# Report on Exam Assignments - Lecture 3

## Task 1

**Read Chapter 3 titled Programming Multi-core and Shared Memory Multiprocessors Using OpenMP (pp. 47–78) in Introduction to Parallel Computing (Trobec et al., 2018)**

### 1. When run with one thread per logical core, threads from Listing 3.1 display their numbers randomly, while those from Listing 3.2 show them in the same order. Explain why.

The key difference between the two listings are the length of the operations. 

In Listing 3.1, the code executes the same, short operation on every thread: printing `omp_get_thread_num`. All threads are effectively competing to print to `stdout` at nearly the same time, resulting in race conditions and seemingly random outputs.

In Listing 3.2, each thread computes a **different** Fibonacci number. Not only is this a longer operation that actually takes measurable time, but also the time is different for each thread: the Fibonacci number to compute depends on the thread id, where higher ids lead to higher calculation times. Now, prints to `stdout` happen after one another, sequentially and without race conditions.

### 2. What do you think, does the code snippet in Listing 3.10 use the cores efficiently, why yes, why no. Consider also the variable size in your argumentation.

**Yes:**

- High degree of parallelization because both for-loops are collapsed and executed in parallel
- No data dependencies within a generation, since data from `plane` is used to compute data in `aux_plane`
    - also no race conditions!

**No:**

- If the size is small, the overhead of parallelizing a double for-loop might hurt performance
    - especially since there are no `complex` operations, single-core sequential execution could be faster for small sizes 
    - it is hard to make a concrete statement here, it all depends on hardware, compiler, etc..
- each iteration of the while-loop creates a new parallel region
    - repeated creation and deletion of thread teams might hurt performance
    - a solution could be to create a parallel region outside the while-loop

### 3. From Lecture 1, take your parallelized version of pi_monte_carlo.cpp and modify it based on the insights from Example 3.5 on computing π using random shooting, particularly the random number generation method. Report the changes you do and their impact on performance