/**
 * @file Circle_Permutation_Algorithm.cpp
 * @brief High-performance Circle Permutation Algorithm (Cross-platform Implementation)
 * @copyright Copyright (c) 2024 [ Yusheng-Hu ]. All rights reserved.
 * @license Licensed under the MIT License.
 * * Program Details:
 * - Implements a specialized circle permutation logic with memory-copy optimizations.
 * - Features: Cross-platform CPU Affinity, High-precision timing (std::chrono), 
 * and manual pointer arithmetic for performance.
 */

#include <cstdio>
#include <cstring>
#include <ctime>
#include <chrono> // Cross-platform high-precision timing

// Linux-specific headers for thread affinity
#ifdef __linux__
#include <sched.h>
#include <pthread.h>
#endif

#define N 14
// #define OUTPUT 1
#define lastIndex (N - 1)
#define secondLastIndex (N - 2)
#define thirdLastIndex (N - 3)

int main()
{
  // Set thread affinity for Linux environment
#ifdef __linux__
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(1, &cpuset); // Set to core 1
  pthread_t current_thread = pthread_self();
  if (pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset) != 0)
  {
    printf("Failed to set thread affinity\n");
  }
  else
  {
    printf("Running on CPU core 1\n");
  }
#endif

  time_t now = time(NULL);
  struct tm *tm = localtime(&now);
  printf("Now time: %02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);

  static int C[N] = {0};
  static int D[N][3 * N] = {0};

  // High-precision timing using std::chrono
  auto start = std::chrono::high_resolution_clock::now();

  int *P1 = &D[lastIndex][0];         
  int *P2 = &D[lastIndex][N];         
  int *P3 = &D[lastIndex][N * 2 - 1]; 

  const size_t memcpy_size = static_cast<size_t>(secondLastIndex) * sizeof(int);

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < i; j++)
    {
      D[i][j] = j;
      D[i][j + i + 1] = j;
    }
    D[i][i] = i;
  }

  int i = thirdLastIndex - 1;
  while (C[0] < 1)
  {
    for (int j = i + 1; j < lastIndex; j++)
    {
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

    for (int circle_index = 0; circle_index < lastIndex; circle_index++)
    {
        D[lastIndex][lastIndex + circle_index] = D[lastIndex][N + circle_index];
        D[lastIndex][N + circle_index] = lastIndex;
    }

    C[thirdLastIndex]++;
    for (i = thirdLastIndex; (i > 0) && (C[i] > i); i--)
    {
      C[i] = 0;
      C[i - 1]++;
    }
  }

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = finish - start;
  printf("\ncircle_test\t%u\t%lf seconds\n", N, duration.count());

  if (D[lastIndex][lastIndex] == 100)
  {
    printf ("rare\n");
  }
  return 0;
}
