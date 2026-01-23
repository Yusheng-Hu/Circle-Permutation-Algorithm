/**
 * @file    pure_circle.cpp
 * @brief   High-Performance Permutation Generator using Circle Algorithm
 * @author  YUSHENG-HU
 * @date    2026-01-23
 * * @details
 * This implementation achieves ultra-high throughput (~16 Giga-perms/sec) by 
 * combining a Non-recursive Plain Changes (PP) generator with a Circular 
 * Permutation (CP) burst logic. 
 * * Key optimizations:
 * 1. Physical Memory Reuse: Uses a 3*N contiguous buffer (Circle_D) to 
 * simulate a circular environment, eliminating complex array rotations.
 * 2. Mirrored Synchronization: Synchronizes the base permutation to 
 * mirrored P2/P3 segments via memcpy for O(1) sliding window access.
 * 3. Incremental PP: Generates (N-2)! base states in-place on P1, 
 * ensuring cache-local operations and minimal branch mispredictions.
 * * License: MIT License
 * Copyright (c) 2026 YUSHENG-HU
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <cstdio>
#include <cstring>
#include <ctime>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sched.h>
    #include <unistd.h>
#endif

#define N 14  
#define lastIndex (N - 1)
#define secondLastIndex (N - 2)

// Platform-independent core affinity
void set_cpu_affinity(int core_id) {
#ifdef _WIN32
    if (!SetThreadAffinityMask(GetCurrentThread(), 1ULL << core_id)) {
        printf("Warning: Could not set CPU affinity to core %d\n", core_id);
    }
#else
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) != 0) {
        printf("Warning: Could not set CPU affinity to core %d\n", core_id);
    }
#endif
}

// Platform-independent timer
double get_time_seconds() {
#ifdef _WIN32
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
#endif
}

int main() {
    set_cpu_affinity(4);

    static int Circle_D[3 * N] = {0}; 
    static int C_PP[N] = {0}; 
    
    int *P1 = &Circle_D[0];         
    int *P2 = &Circle_D[N];           
    int *P3 = &Circle_D[N + (N - 1)]; 

    for (int j = 0; j < N; j++) P1[j] = j;

    unsigned long long total_perms = 0;
    double start_time = get_time_seconds();

    while (C_PP[0] < 1) {
        // [1] Sync mirror
        memcpy(P2, P1, (N - 1) * sizeof(int));
        memcpy(P3, P1, (N - 1) * sizeof(int));

        // [2] CP burst phase
        for (int circle_index = 0; circle_index < lastIndex; circle_index++) {
            total_perms += N;
            Circle_D[lastIndex + circle_index] = Circle_D[N + circle_index];
            Circle_D[N + circle_index] = lastIndex;
        }

        // [3] PP increment carry and in-place swap
        int i = N - 3; 
        C_PP[i]++;
        while (i > 0 && C_PP[i] > i) {
            int target = C_PP[i] - 1;
            int temp = P1[i]; P1[i] = P1[target]; P1[target] = temp;
            C_PP[i] = 0;
            i--;
            C_PP[i]++;
        }
        if (C_PP[0] < 1) {
            int target = C_PP[i] - 1;
            if (target >= 0) {
                int temp = P1[i]; P1[i] = P1[target]; P1[target] = temp;
            }
        }
        P1[lastIndex] = lastIndex; 
    }

    double duration = get_time_seconds() - start_time;

    printf("\n--- Performance Result ---");
    printf("\nN: %d", N);
    printf("\nTotal Permutations: %llu", total_perms);
    printf("\nTime: %.4f seconds", duration);
    if (duration > 0) {
        printf("\nSpeed: %.2f Giga-perms/sec", (double)total_perms / duration / 1e9);
    }
    printf("\n--------------------------\n");

    return 0;
}
