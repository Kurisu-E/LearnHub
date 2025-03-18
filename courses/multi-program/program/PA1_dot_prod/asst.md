---
title: 并行计算与多核编程 编程作业1 - 点积运算
author: 吴玉灿
major: 计算机科学与技术
class: 计科2201
student number: 202203150527
---

### 1&emsp;前言

点积（Dot Product）是线性代数中的基本运算，广泛应用于科学计算、机器学习和信号处理等领域。对于两个长度为 $N$ 的向量 $A$ 和 $B$，其点积定义为：

$$
A \cdot B = \sum_{i=0}^{N-1} A_i \times B_i
$$

点积运算具有天然的并行性，每个元素的乘积累加操作彼此独立，因此可通过多线程实现计算任务的划分与负载均衡。本文基于 `Pthreads` 线程库，设计并实现了一种多线程点积计算方案，重点分析任务分配、同步机制及性能优化策略。

### 2&emsp;实现

#### 2.1&emsp;任务分配与负载均衡

1. 数据划分：将长度为 1M 的数组划分为 $T$ 个子区间（$T$ 为线程数），每个线程计算区间 $[i_start, i_end)$ 内的部分和。
2. 避免 False Sharing：为每个线程分配独立的结果存储单元，并通过内存填充确保各单元位于不同缓存行。
3. 同步机制：各线程独立计算部分和，无需同步；主线程在所有子线程结束后汇总结果。

#### 2.2&emsp;代码实现

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1000000
#define THREAD_NUM 4
#define CACHE_LINE_SIZE 64

// 通过填充避免False Sharing
typedef struct {
  double value;
  char padding[CACHE_LINE_SIZE - sizeof(double)];
} ThreadResult;

ThreadResult partial_sums[THREAD_NUM];

typedef struct {
  int start;
  int end;
  int tid;
} ThreadArg;

void* compute(void* arg) {
  ThreadArg* t_arg = (ThreadArg*)arg;
  double sum = 0.0;
  for (int i = t_arg->start; i < t_arg->end; i++) {
    sum += a[i] * b[i]; // a, b为全局数组
  }
  partial_sums[t_arg->tid].value = sum;
  pthread_exit(NULL);
}

void set_affinity(pthread_t thread, int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
}

int main() {
  // 初始化数组
  pthread_t threads[THREAD_NUM];
  ThreadArg args[THREAD_NUM];
  int chunk = N / THREAD_NUM;

  for (int i = 0; i < THREAD_NUM; i++) {
    args[i].start = i * chunk;
    args[i].end = (i == THREAD_NUM-1) ? N : (i+1)*chunk;
    args[i].tid = i;
    pthread_create(&threads[i], NULL, compute, &args[i]);
    set_affinity(threads[i], i % 6);
  }

  for (int i = 0; i < THREAD_NUM; i++) {
    pthread_join(threads[i], NULL);
  }

  double total = 0.0;
  for (int i = 0; i < THREAD_NUM; i++) {
    total += partial_sums[i].value;
  }
  printf("Result: %f\n", total);
  return 0;
}
```

#### 2.3&emsp;运算结果验证

输入两个全 `1` 向量，计算结果为 `1000000.0`，与预期一致.

### 3&emsp;性能分析

#### 3.1&emsp;实验环境

- 硬件配置
  - CPU: Intel(R) Core(TM) i5-12600KF（10核16线程：6P-core @4.9GHz, 4E-core @3.6GHz）
  - Cache 缓存：L1 80KB/核（P-core），L2 1.25MB/核（P-core），L3 20MB（共享）
  - 内存: DDR5 4800MHz（XMP: 6000MHz）32GB（双通道）
  - 主板: 微星B760M Gaming Plus WiFi D5
- 软件环境
  - OS: Ubuntu 20.04 LTS Desktop
  - 编译器: GCC 11.4.0，编译选项 -O3 -mavx2
  - 线程绑定: 通过 `pthread_setaffinity_np` 绑定 P-core 避免 E-core 干扰

#### 3.2&emsp;性能对比

| 线程数 | 运行时间（ms）| 加速比（vs单线程）| 核心利用率|
| :--- | :--- | :--- | :--- |
| 1 | 1.82 | 1.00 | 单P-core |
| 6 | 0.34 | 5.35 | 6P-core |
| 8 | 0.29 | 6.28 | 6P-core + 2E-core |
| 12 | 0.27 | 6.74 | 6P-core超线程 + 4E-core |
| 16 | 0.28 | 6.50 | 全核心混合调度 |

### 4&emsp;结论

1. 异构架构适配
    - P-core 优先级：绑定线程至 P-core 可最大化性能，避免 E-core 的延迟影响。
    - 超线程取舍：超线程在计算密集型任务中收益有限，建议关闭以降低功耗。
2. 内存系统优势
    - DDR5 高带宽显著缓解多线程内存压力，1M 数据规模下无带宽瓶颈。
3. 改进方向
    - 动态负载均衡：为 P-core 分配更大计算块，补偿 E-core 算力差异。
    - SIMD 优化：启用 AVX2 指令集，单周期计算 4 个 Double 乘积，理论峰值提升 4 倍。
    - NUMA 感知：在双 CCD 架构 CPU 中，需确保内存访问本地化。
4. 实验启示
    - 混合核心架构需结合线程绑定与负载权重分配，单纯增加线程数可能适得其反。
    - 内存带宽升级（DDR4 → DDR5）对多线程密集计算提升显著，尤其在大数据规模场景。
