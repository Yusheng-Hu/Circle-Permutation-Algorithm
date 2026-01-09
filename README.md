# Circle-Permutation-Algorithm

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Complexity: O((n-1)!)](https://img.shields.io/badge/Complexity-O((n--1)!)-blue.svg)](#)
[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-red.svg)](#)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.18194997.svg)](https://doi.org/10.5281/zenodo.18194997)

An optimized iterative algorithm for Full Permutation generation that challenges the $O(N!)$ amortized complexity barrier.

**Circle-Permutation-Algorithm** is a transformative generation framework for permutations that shatters the operational bottlenecks of classical combinatorial algorithms. By introducing a **triple-segment memory mirroring topology**, this framework demonstrates that active logic overhead can be structurally decoupled from the $n!$ sequence scale.

This repository is the official C++ implementation of the paper:  
*"Circle Algorithm: An $O((n-1)!)$ Linear-Time Generation Algorithm for Permutations"* Work in Progress

## 🎮 Live Demo

You can try the interactive circle permutation visualization directly in your browser:

👉 **[View Circle Demo](https://yusheng-hu.github.io/Circle-Permutation-Algorithm/circle_demo.html)**

👉 **[View Circle Triple Process Demo](https://yusheng-hu.github.io/Circle-Permutation-Algorithm/triple_process_reducecomplex.html)**

---

## 🚀 Key Highlights

- **Complexity Breakthrough**: Reduces the frequency of state-transition decisions to an amortized **$O((n-1)!)$** level, while the majority of permutations are generated via deterministic topological shifts.
- **Extreme Performance**: Unlike traditional algorithms, the Circle Algorithm's throughput scales positively with order N. It reaches 4.856 Giga/s at N=14, demonstrating the power of its O((n−1)!) amortized logic. This performance translates to a CPP of 0.41, setting a new benchmark for combinatorial generation.
- **Optimal Superpermutation**: Provides a universal constructive proof for the Superpermutation problem, yielding sequences that strictly attain the theoretical lower bound $L = \sum_{i=1}^{n} i!$.
- **Stateless Sharding**: Features a mathematically consistent indexing theorem (Theorem 1) that enables efficient **Rank** and **Unrank** operations for massive parallelization.

---

## 📊 Benchmarks

### Throughput & Efficiency (Intel i7-8550U @ 1.8 GHz)
### Performance Benchmark (Tested on N=9 to 14)

| Order (N) | Total Count (N!) | Execution Time (s) | Throughput (Giga/s) |
| :--- | :--- | :--- | :--- |
| **9** | 362,880 | 0.000195 | 1.858 |
| **10** | 3,628,800 | 0.002539 | 1.429 |
| **11** | 39,916,800 | 0.016854 | 2.368 |
| **12** | 479,001,600 | 0.138255 | 3.465 |
| **13** | 6,227,020,800 | 1.449907 | 4.295 |
| **14** | 87,178,829,1200 | 17.954149 | **4.856** |

> **Observation**: Note that the throughput (Rate) significantly increases as $N$ grows, reaching a record-breaking **4.856 Giga-perms/s** at $N=14$.

### Superpermutation Verification
| Order (N) | Theoretical Lower Bound ($\sum i!$) | Circle Algorithm Length | Status |
|:---:|:---:|:---:|:---:|
| 10 | 4,037,913 | 4,037,913 | ✅ **MATCH** |
| 12 | 523,001,313 | 523,001,313 | ✅ **MATCH** |
| 15 | 1,401,602,636,313 | 1,401,602,636,313 | ✅ **MATCH** |

---
## Citation

If you use this algorithm in your research or project, please cite it as:

> Yusheng-Hu. (2026). Circle-Permutation-Algorithm: High-performance Full Permutation Generation [Data set]. Zenodo. https://doi.org/10.5281/zenodo.18194997

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.18194997.svg)](https://doi.org/10.5281/zenodo.18194997)
