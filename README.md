# Circle-Permutation-Algorithm

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Complexity: O((n-1)!)](https://img.shields.io/badge/Complexity-O((n--1)!)-blue.svg)](#)
[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-red.svg)](#)

**Circle-Permutation-Algorithm** is a transformative generation framework for permutations that shatters the operational bottlenecks of classical combinatorial algorithms. By introducing a **triple-segment memory mirroring topology**, this framework demonstrates that active logic overhead can be structurally decoupled from the $n!$ sequence scale.

This repository is the official C++ implementation of the paper:  
*"Circle Algorithm: An $O((n-1)!)$ Linear-Time Generation Algorithm for Permutations"*

---

## 🚀 Key Highlights

- **Complexity Breakthrough**: Reduces the frequency of state-transition decisions to an amortized **$O((n-1)!)$** level, while the majority of permutations are generated via deterministic topological shifts.
- **Extreme Performance**: Achieves a peak throughput of **4.006 Giga-permutations/sec** (on Intel Core i7-8550U), with a Cycles Per Permutation (CPP) of just **0.45**.
- **Optimal Superpermutation**: Provides a universal constructive proof for the Superpermutation problem, yielding sequences that strictly attain the theoretical lower bound $L = \sum_{i=1}^{n} i!$.
- **Stateless Sharding**: Features a mathematically consistent indexing theorem (Theorem 1) that enables efficient **Rank** and **Unrank** operations for massive parallelization.



---

## 📊 Benchmarks

### Throughput & Efficiency (Intel i7-8550U @ 1.8 GHz)
| Order (N) | Total Count (N!) | Time (s) | Rate (Giga-perm/s) | CPP (Cycles/Perm) |
|:---:|:---:|:---:|:---:|:---:|
| 12 | 479,001,600 | 0.2091 | 2.290 | 0.79 |
| 13 | 6,227,020,800 | 1.8786 | 3.315 | 0.54 |
| 14 | 87,178,291,200 | 21.7645 | **4.006** | **0.45** |

### Superpermutation Verification
| Order (N) | Theoretical Lower Bound ($\sum i!$) | Circle Algorithm Length | Status |
|:---:|:---:|:---:|:---:|
| 10 | 4,037,913 | 4,037,913 | ✅ **MATCH** |
| 12 | 523,001,313 | 523,001,313 | ✅ **MATCH** |
| 15 | 1,401,602,636,313 | 1,401,602,636,313 | ✅ **MATCH** |

---
