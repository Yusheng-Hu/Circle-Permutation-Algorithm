/**
 * @file Circle_Permutation_Algorithm.cpp
 * @brief High-performance Circle Permutation Algorithm (Strictly Preserved Logic)
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

#define N 15
// Keep original OUTPUT toggle for verification
// #define OUTPUT 1

#define lastIndex (N - 1)
#define secondLastIndex (N - 2)
#define thirdLastIndex (N - 3)

int main() {
    // 1. Set CPU Affinity (Linux equivalent of Windows SetThreadAffinityMask)
    // We bind to Core 0 for consistency on GitHub Runners
#ifdef __linux__
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset); 
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    printf("Running on CPU core 0\n");
#else
    printf("Running on CPU core 2\n");
#endif

    // Metadata for YAML parser
    printf("PARAM_N: %d\n", N);

    time_t now = time(NULL);
    struct tm *tm_ptr = localtime(&now);
    printf("Now time: %02d:%02d:%02d\n", tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);

    static int C[N] = {0};
    static int D[N][3 * N] = {0};

    // 2. High-precision timing using std::chrono (QPC Replacement)
    auto start_point = std::chrono::high_resolution_clock::now();

    // --- START OF ORIGINAL PRESERVED LOGIC ---
    int *P1 = &D[lastIndex][0];
    int *P2 = &D[lastIndex][N];
    int *P3 = &D[lastIndex][N * 2 - 1];

    const size_t memcpy_size = static_cast<size_t>(secondLastIndex) * sizeof(int);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            D[i][j] = j;
            D[i][j + i + 1] = j;
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
            #ifdef OUTPUT
            // This is your original triple-nested loop for rotation output
            for (int circlehead = circle_index; circlehead < circle_index + N; circlehead++) {
                for (int oneperm = circlehead; oneperm < circlehead + N; oneperm++) {
                    printf("%d ", D[lastIndex][oneperm]);
                }
                printf("\n");
            }
            #endif

            D[lastIndex][lastIndex + circle_index] = D[lastIndex][N + circle_index];
            D[lastIndex][N + circle_index] = lastIndex;
        }

        C[thirdLastIndex]++;
        for (i = thirdLastIndex; (i > 0) && (C[i] > i); i--) {
            C[i] = 0;
            C[i - 1]++;
        }
    }
    // --- END OF ORIGINAL PRESERVED LOGIC ---

    auto end_point = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_point - start_point;
    double duration = diff.count();

    printf("\ncircle.exe\t%u\t%lf", N, duration);
    printf("\nRESULT_TIME: %lf seconds\n", duration);

    // Minimal-cost Anti-optimization Barrier
    // Volatile prevents the compiler from assuming D is unused
    int volatile* anti_opt = &D[lastIndex][lastIndex];
    if (*anti_opt == 100) printf("rare\n");

    return 0;
}



