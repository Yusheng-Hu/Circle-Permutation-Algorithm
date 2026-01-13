/**
 * @file Circle_Permutation_Algorithm.cpp
 * @brief High-performance Circle Permutation Algorithm (Cross-platform)
 * @copyright Copyright (c) 2024 [ Yusheng-Hu ]. All rights reserved.
 * @license Licensed under the MIT License.
 */

#include <cstdio>
#include <cstring>
#include <ctime>
#include <chrono>

#ifdef __linux__
#include <sched.h>
#include <pthread.h>
#endif

// Current configuration
#define N 13
#define lastIndex (N - 1)
#define secondLastIndex (N - 2)
#define thirdLastIndex (N - 3)

int main() {
#ifdef __linux__
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
#endif

    static int C[N] = {0};
    static int D[N][3 * N] = {0};
    unsigned long long total_count = 0;

    auto start = std::chrono::high_resolution_clock::now();

    int *P1 = &D[lastIndex][0];
    int *P2 = &D[lastIndex][N];
    int *P3 = &D[lastIndex][N * 2 - 1];
    const size_t memcpy_size = static_cast<size_t>(secondLastIndex) * sizeof(int);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            D[i][j] = j; D[i][j + i + 1] = j;
        }
        D[i][i] = i;
    }

    int i = thirdLastIndex - 1;
    while (C[0] < 1) {
        for (int j = i + 1; j < lastIndex; j++) {
            const int* src_ptr = &D[j - 1][C[j - 1]];
            memcpy(D[j], src_ptr, static_cast<size_t>(j) * sizeof(int));
            memcpy(&D[j][j + 1], src_ptr, static_cast<size_t>(j) * sizeof(int));
        }

        const int *src_ptr = &D[thirdLastIndex][C[thirdLastIndex]];
        memcpy(P1, src_ptr, memcpy_size);
        *(P1 + secondLastIndex) = secondLastIndex;
        *(P1 + lastIndex) = lastIndex;
        memcpy(P2, src_ptr, memcpy_size);
        *(P2 + secondLastIndex) = secondLastIndex;
        memcpy(P3, src_ptr, memcpy_size);

        for (int circle_index = 0; circle_index < lastIndex; circle_index++) {
            D[lastIndex][lastIndex + circle_index] = D[lastIndex][N + circle_index];
            D[lastIndex][N + circle_index] = lastIndex;
        }
        total_count += lastIndex;

        C[thirdLastIndex]++;
        for (i = thirdLastIndex; (i > 0) && (C[i] > i); i--) {
            C[i] = 0; C[i - 1]++;
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    
    // Crucial: Fixed labels for reliable parsing
    printf("\nRESULT_TIME: %lf seconds\n", elapsed.count());
    printf("CHECKSUM_COUNT: %llu\n", total_count);

    return 0;
}

