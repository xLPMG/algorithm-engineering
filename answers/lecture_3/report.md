# Report on Exam Assignments - Lecture 3

## Task 1

**Read Chapter 3 titled Programming Multi-core and Shared Memory Multiprocessors Using OpenMP (pp. 47–78) in Introduction to Parallel Computing (Trobec et al., 2018)**

### 1. When run with one thread per logical core, threads from Listing 3.1 display their numbers randomly, while those from Listing 3.2 show them in the same order. Explain why.

The key difference between the two listings are the length of the operations. 

In Listing 3.1, executes the same, short operation: printing `omp_get_thread_num`. All threads are effectively competing to print to `stdout` at nearly the same time, resulting in race conditions and seemingly random outputs.

In Listing 3.2, each thread computes a **different** Fibonacci number. Not only is this a longer operation that actually takes measurable time, but also the time is different for each thread: the Fibonacci number to compute depends on the thread id, where higher ids lead to higher calculation times. Now, prints to `stdout` happen after one another, sequentially and without race conditions.

### 2. What do you think, does the code snippet in Listing 3.10 use the cores efficiently, why yes, why no. Consider also the variable size in your argumentation.

### 3. From Lecture 1, take your parallelized version of pi_monte_carlo.cpp and modify it based on the insights from Example 3.5 on computing π using random shooting, particularly the random number generation method. Report the changes you do and their impact on performance