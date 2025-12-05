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

## Task 3

**Read the paper Analyzing Vectorized Hash Tables Across CPU Architectures. Discuss two things you find particularly interesting.**

