# Report on Exam Assignments - Lecture 9

## Task 1

**How do bandwidth-bound computations differ from compute-bound computations?**

Bandwidth-bound computations are limited by the memory bandwidth of the system. Here, the CPU could potentially perform more calculations, but it is waiting for data to be transferred from memory to the CPU. This situation appears for example when doing a relatively cheap operation (like addition) on a large dataset like a matrix that does not fit into the CPU cache. The CPU has to wait for data to be loaded from the main memory, which is much slower than accessing data from the cache. As a result, the overall performance is limited by how fast data can be moved between memory and the CPU, rather than how fast the CPU can perform calculations.

Compute-bound computations are limited by the processing power of the CPU. In this case, the CPU is fully utilized and cannot perform calculations any faster, even if data is available in the cache. This situation appears when performing complex calculations that require a lot of computational resources on relatively small data. Here, the performance is determined by the speed of the CPU and its ability to execute instructions efficiently.

While both scenarios can lead to performance bottlenecks, the key difference is what limits the performance: memory bandwidth for bandwidth-bound computations and CPU processing power for compute-bound computations. Optimizing for bandwidth-bound computations often involves improving data locality (temporal & spatial locality) and reducing memory access times, while optimizing for compute-bound computations focuses on increasing CPU efficiency through techniques like SIMD and ILP.

## Task 2

**Explain why temporal locality and spatial locality can improve program performance.**

Temporal Locality describes the reuse of data within a short time frame. A program with good temporal locality accesses the same memory locations multiple times in a short period. This is beneficial for performance because when data is accessed, it is typically loaded into the CPU cache(s). If the same data is needed again soon after, it can be read from the cache which is much faster than accessing the main memory. This reduces the number of slow memory accesses, leading to improved performance. If data is not reused in the near future, it may be removed from the cache already to make space for new data, leading to a cache miss and a slower main memory access.

Spatial Locality refers to the use of data elements within nearby memory locations. Programs with good spatial locality access memory locations that are close to each other in a short period. This is beneficial for performance because when a memory location is accessed, the CPU typically loads not only that specific location but also adjacent memory locations into the cache (cache line). If the program accesses nearby data soon after, it can take advantage of the data already being in the cache, reducing the need for additional slow memory accesses. This leads to fewer cache misses and improved overall performance. One example of spatial locality is the use of small strides (at best unit stride) when accessing memory.

## Task 3

**Select one slide from the lecture, research more about the topic, and report on it.**

## Task 4

**Read the paper An Overview of Cache Optimization Techniques and Cache-Aware Numerical Algorithms. Discuss two things you find particularly interesting.**