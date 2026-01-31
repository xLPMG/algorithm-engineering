# Report on Exam Assignments - Lecture 8

## Task 1

**Select one slide from the lecture, research more about the topic, and report on it.**

For this task, I will report on the topic of Instruction-Level Parallelism (ILP), which was introduced on slides 6 and 7.
Main source: https://www.geeksforgeeks.org/computer-organization-architecture/instruction-level-parallelism/.

Instruction-Level Parallelism (ILP) refers to the capability of a processor to execute multiple instructions at the same time.

This is different from other forms of parallelism, such as SIMD (Single Instruction, Multiple Data) which focuses on the execution of a single instruction on multiple data points simultaneously. Furthermore, it also differs from higher forms of parallelism like multi-threading or multicore processing, since ILP operates at the instruction level within a single processor core.

ILP can be achieved either by executing instructions simultaneously or by utilizing gaps between successive operations that are created due to the latencies. Typically, a core of an ILP processor contains multiple execution units, which can perform different types of operations, such as integer arithmetic, floating point arithmetic or branching. If all instructions depend on the result of the previous instruction, only one execution unit is used at a time while the others remain idle. However, if there are independent instructions that can be executed in parallel, multiple execution units can be utilized simultaneously, thereby improving performance. How much control the compiler (software) or the hardware has over exploiting ILP depends on the architecture of the processor.

We can use this distinction to classify ILP architectures into three categories:
- **Sequential Architecture**: the program does not give the processor any information about parallelism. The hardware is responsible for identifying and exploiting ILP.
- **Dependence Architecture**: the program provides some information about dependencies between instructions, which helps the hardware to exploit ILP more effectively.
- **Independence Architecture**: the program provides information on which operations are independent of each other, allowing the hardware to execute them in parallel.

Lastly, I want to mention the pros and cons of ILP:

**Pros:**

- Improved Performance: ILP can significantly improve the performance of processors (faster program execution, better system throughput)
- Efficient Resource Utilization: ILP can help to utilize the hardware resources more efficiently by keeping multiple execution units working simultaneously
- Reduced Instruction Dependency: ILP can reduce instruction dependencies, allowing for more instructions to be executed in parallel
- Increased Throughput: ILP can help to increase the overall throughput of processors by allowing multiple instructions to be executed simultaneously or out-of-order

**Cons:**
- Increased Complexity: Implementing ILP can increase the complexity of processor design, which can lead to higher costs
- Instruction Overhead: ILP can introduce additional instruction overhead, which can reduce the overall performance benefits
- Data Dependencies: ILP can be limited by data dependencies between instructions, which can prevent certain instructions from being executed in parallel
- Reduced Energy Efficiency: ILP can lead to increased power consumption (due to extra hardware resources)

## Task 2

**What do the metrics latency and throughput tell you about the performance of an intrinsic function?**

Latency describes the time it takes to complete a single operation or instruction from start to finish. For example a latency of 5 cycles means that once an instruction starts executing, it will take 5 CPU cycles to complete.

Throughput describes how many operations or instructions can be completed in a given amount of time. For example a throughput of 2 instructions per cycle means that on average, 2 instructions can be completed every CPU cycle.

These metrics affect performance differently depending on the structure of the code. If each instruction depends on the result of the previous one, then the latency has the dominant effect on performance, because each instruction must wait for the result of the previous one. In this case, a long latency directly limits how fast the instructions can be executed, thus reducing overall performance.

However for independent instructions, the CPU can use ILP to execute multiple instructions simultaneously. In this situation, throughput becomes more important than latency, because the processor can keep its execution units busy. A high throughput allows more instructions to be completed in a given time, improving overall performance.

ILP is most effective when the workload contains many independent operations, such as in loop unrolling or vectorized code, or algorithms where computations do not depend on each others results. With ILP, individual instruction latencies can become less significant, as the CPU can overlap the execution of multiple instructions. On the other hand, if there are many dependencies between instructions, ILP is less effective, and latency becomes the limiting factor for performance.

## Task 3

**Read the paper** _Analyzing Vectorized Hash Tables Across CPU Architectures_**. Discuss two things you find particularly interesting.**

In previous lectures, we have discussed different revisions of x86 instruction sets, such as SSE, AVX, AVX2 and AVX-512. Personally, I am more interested in ARM architectures, which are also discussed in the given paper. The ARM architecture is designed and developed by the ARM Limited company, which licenses its designs to other companies that manufacture ARM-based processors. ARM processors are widely used in mobile devices and even in the second-fastest supercomputer. Similarly to x86, the ARM ISA has also evolved over time to include SIMD capabilities. Since ARMv8-A, the SIMD extension called NEON is included in all ARM A-profile CPUs and features 16 128-bit vector registers. These can be addressed in different ways, for example as 16 8-bit values, 8 16-bit values, 4 32-bit values or 2 64-bit values. This allows for parallel processing of multiple data points in a single instruction, similar to the AVX instruction set on x86 architectures. In 2016, ARM introduced the Scalable Vector Extension (SVE). SVE is a more advanced SIMD extension features 32 vector registers with lengths ranging from 128 bits to 2048 bits, depending on the hardware implementation. Programming for SVE requires "vector-length agnostic" code, meaning that the same program can run on different hardware with varying vector lengths without modification. Similar to AVX-512, SVE supports predication, which enables the selection of individual elements of SVE registers (masking).

One of the more recent revisions of the ARM architecture is Armv9.2-A, which enabled support for the Scalable Matrix Extension (SME). This was not discussed in the paper, presumably because the paper was published before SME became available in processors. One example is the Apple M4 processor, which was released on May 7, 2024. SME introduced new MOPA (Matrix Outer Product Accumulate) instruction, which can perform matrix multiplications more efficiently than Neon or SVE implementations. SME also introduced a two-dimensional ZA array, which can be used to store matrices and perform not only matrix operations, but also various slicing operations along vertical and horizontal axes. (Source: https://scalable.uni-jena.de/opt/pbtc/chapters/sme.html)

The second topic that I found interesting is the Vectorized Linear Probing (VLP) hashing scheme. Like the scalar Linear Probing (LP), it handles hash collisions by checking the next slot until it finds the key or an empty one. VLP does this using SIMD instructions, allowing it to compare several keys at once. It only works with integer keys and uses a struct-of-arrays (SoA) layout with separate key, value, and validity arrays. The algorithm loads as many keys as possible into a vector register, compares them in parallel, and checks the validity bits to stop when an empty slot is reached.

The paper describes two variants: TEST and NOTEST. TEST first checks if any key in the vector matches, and only then extracts the matching index. NOTEST always extracts an index, which may be invalid. Even though TEST sounds like it adds considerable overhead, the experiments showed that the match check is very cheap, so TEST consistently performs better because it avoids unnecessary index extraction. Despite being a vectorized version of LP, using VLP with 64-bit keys doesn't improve insert and lookup performance. The paper explains that this is due to the small degree of parallelism and the additional algorithmic overhead. An approach to improve VLP is to reduce the two random memory loads per probe, increase the degree of parallelism to meaningfully use 128-bit registers and lastly to become independent of the key data type (e.g. whether 32-bit or 64-bit keys are used).