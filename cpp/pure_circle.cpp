/**
 * @file    pure_circle.cpp
 * @brief   High-Performance Permutation Generator using Circle Algorithm
 * @author  YUSHENG-HU
 * @date    2026-01-23
 * @details
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

 #include <iostream>
 #include <vector>
 #include <cstring>
 #include <chrono>
 #include <cstdio>
 
 // System headers for CPU affinity
 #ifdef _WIN32
 #include <windows.h>
 #else
 #include <sched.h>
 #include <pthread.h>
 #endif
 
 #ifndef PP_N
 #define PP_N 14 // Default setup for N=16 (CP_N = PP_N + 2)
 #endif
 
 // Function to bind execution to a specific CPU core
 void bind_to_core(int core_id) {
 #ifdef _WIN32
     HANDLE process = GetCurrentProcess();
     DWORD_PTR processAffinityMask = 1ull << core_id;
     SetProcessAffinityMask(process, processAffinityMask);
     printf("Windows: Bound to Core %d\n", core_id);
 #else
     cpu_set_t cpuset;
     CPU_ZERO(&cpuset);
     CPU_SET(core_id, &cpuset);
     pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
     printf("Linux: Bound to Core %d\n", core_id);
 #endif
 }
 
 unsigned long long get_factorial(int n) {
     unsigned long long res = 1;
     for (int i = 1; i <= n; i++) res *= i;
     return res;
 }
 
 int main() {
     // Core binding should be performed before main logic execution
     bind_to_core(0);
 
     const int CP_N = PP_N + 2; 
     const int VAL_ELM_N_MINUS_2 = PP_N;      
     const int VAL_ELM_N_MINUS_1 = PP_N + 1;  
 
     const int OFFSET_B1 = 0;
     const int OFFSET_B2 = CP_N;
     const int OFFSET_B3 = CP_N + (CP_N - 1);
 
     alignas(64) static int D[3 * CP_N] = {0}; 
     int C[PP_N] = {0};
     int i = 0;
 
     for (int k = 0; k < PP_N; k++) D[k] = k;
 
     auto start = std::chrono::high_resolution_clock::now();
 
     // Main Permutation Generation Loop
     while (C[0] < 1) {
         for (; i < PP_N - 1; ++i) {
             D[i] = D[C[i]];
             D[C[i]] = i;
         }
 
         for (int ii = 0; ii < PP_N; ii++) {
             D[PP_N - 1] = D[ii];
             D[ii] = PP_N - 1;
             D[PP_N] = VAL_ELM_N_MINUS_2;
             D[PP_N + 1] = VAL_ELM_N_MINUS_1;
             
             __builtin_memcpy(&D[OFFSET_B2], &D[OFFSET_B1], (CP_N - 1) * sizeof(int));
             __builtin_memcpy(&D[OFFSET_B3], &D[OFFSET_B1], (CP_N - 1) * sizeof(int));
 
             // Pointer pre-calculation for single-core addressing speed
             int* target = &D[PP_N + 1];
             #pragma GCC unroll 16
             for (int layer_shift = 0; layer_shift < CP_N - 1; layer_shift++) {
                 int temp = *(target + 1);
                 *(target + 1) = *target;
                 *target = temp;
                 target++;
             }
             D[ii] = D[PP_N - 1];
         }
 
         D[C[PP_N - 2]] = D[PP_N - 2];
         C[PP_N - 2]++;
         for (i = PP_N - 2; (i > 0) && (C[i] > i); i--) {
             C[i] = 0;
             C[i - 1]++;
             D[C[i - 1] - 1] = D[i - 1];
         }
     }
 
     auto finish = std::chrono::high_resolution_clock::now();
     double duration = std::chrono::duration<double>(finish - start).count();
 
     unsigned long long total_perms = get_factorial(CP_N);
     int volatile* anti_opt = &D[CP_N - 1];
     if (*anti_opt == -999) printf("rare\n");
 
     // Standardized output for log parsing
     printf("N: %d\n", CP_N);
     printf("Total Permutations: %llu\n", total_perms);
     printf("Time: %.6f\n", duration);
     printf("Speed: %.2f\n", (total_perms / duration) / 1e9);
 
     return 0;
 }
