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

For this task I researched more about the Processor–Memory Gap, presented on Slide 4.
To gather more information on this topic, I referred to this article: https://community.juniper.net/blogs/sharada-yeluri/2022/08/22/tearing-down-memory-wall
It explains the whole situation and possible solutions really well.

Over the years, CPU performance has improved at a much faster rate compared to memory performance. This has left a gap between the speed of the CPU and the speed of memory access, known as the Processor–Memory Gap or the Memory Wall.

All modern computers follow the Von Neumann architecture, where the CPU and memory are separate components connected by a bus. The program itself and the data it operates on are stored in the memory, and the CPU fetches instructions and data from memory to perform computations. As CPU speeds increase, the memory is not able to keep up, leading to situations where the CPU is idle, waiting for data to be fetched from memory. This can lead to significant performance bottlenecks.

In this class, we have already learned about a few solutions to this problem:

1. Caches: These are smaller but faster types of memory located closer to the CPU. They store frequently accessed data and instructions, reducing the time it takes for the CPU to access this information compared to fetching it from main memory. The use of caches can be further improved by implementing cache hierarchies (L1, L2, L3), pre-fetching mechanisms, and by the developer/compiler by optimizing for temporal and spatial locality.
2. Parallel Computing: Although this does not directly solve the performance bottleneck for a single task, multi-threading can improve the overall throughput of the CPU. While one thread is waiting for data from memory, other threads can be executed in the meantime.

The third solution presented in the source was not covered in the lecture:

3. In Package High Bandwidth Memory (HBM): This technology describes a high bandwidth memory where multiple DRAM dies are stacked vertically. This stacking is able to achieve a higher density. Furthermore, HBM connects to the CPU/GPU/SOC using an interposer, which allows for a much wider bus (~1024bit) compared to traditional memory connections. This reduces latency and power consumption while increasing bandwidth. However, even with these improvements, the latencies are still 15-20x compared to the SRAMs used in caches due to the latency involved in accessing the memory stack and the path through the interposer.

Lastly, I want to talk about a future trend: 3D Processing.
3D Processing involves stacking memory and processing units vertically in a single package. Here, logic, SRAM and DRAM dies are connected using hybrid bonding using tiny copper interconnects. The benefit of this approach is that the interconnects from memory to processing units are not confined to the edges of the dies, but can be placed across the entire surface area. This allows for much wider buses and shorter distances, leading to significantly reduced latency and increased bandwidth. Current issues of this technology are heat dissipation and manufacturing complexity. The increased power density leads to higher temperatures, which in turn needs more complex cooling solutions.

## Task 4

**Read the paper** _An Overview of Cache Optimization Techniques and Cache-Aware Numerical Algorithms_**. Discuss two things you find particularly interesting.**

The two things I found particularly interesting in this paper are **Loop Fusion** and **Data Prefetching**.

**Loop Fusion** is a data optimization technique where two or more loops that iterate over the same range are combined into a single loop. The inverse of loop fusion is loop distribution or loop fission, which breaks a single loop into multiple loops with the same iteration space. The main goal of loop fusion is to improve temporal locality, expose parallelism and make loop iterations vectorizable. By combining loops, the resulting loop contains more instructions in its body and therefore offers increased instruction level parallelism. It also reduces loop overhead, as there are fewer loop control instructions to execute. Additionally, loop fusion can help with temporal locality: imagine a loop that loads data into the cache, followed by another loop that further processes that data. If the data is large enough to not fit into the cache, it may be evicted before the second loop can use it. By fusing the loops, the data is processed immediately after being loaded, increasing the chances that it remains in the cache.

**Data Prefetching** is a technique used to reduce memory latency by loading data into the cache before it is actually needed by the CPU. The idea is to minimize first time cache misses by predicting which data will be needed in the near future and fetching it in advance, as this is not addressed by data optimization techniques like loop fusion. When the CPU requests data that is not in the cache, it has to wait for the data to be fetched from main memory, which is much slower. By prefetching data, the CPU can have the required data ready in the cache when it needs it, reducing wait times and improving overall performance. In practice, this can be realized using software: many modern microprocessors implement a prefetch instruction which is issued as a regular instruction. It works similarly to a load instruction, but does not forward the data to the CPU. Furthermore, the prefetch instruction is often interpreted as a hint, meaning that the CPU may choose to ignore it. It should be noted that prefetching also comes with overhead: the prefetch instruction itself takes up space in the instruction cache and uses CPU cycles to execute. Additionally, the memory address needs to be calculated once during the prefetching and once during the actual load. The second way to implement prefetching is through hardware: a simple approach is to prefetch the next memory block after a memory access.
In conclusion, data prefetching is a powerful technique to reduce memory latency and improve performance, especially in applications with predictable memory access patterns. However, if a prefetched data replaces useful data in the cache before it is used, it can actually reduce performance by increasing bus traffic and cache misses.

Side note: unfortunately I could only write a short discussion this week. Solving the exam assignments, especially reading the papers, takes quite some time. Together with the project work, there was not much time left for me to write a longer report.