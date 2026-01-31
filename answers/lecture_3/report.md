# Report on Exam Assignments - Lecture 3

## Task 1

**Read Chapter 3 titled** _Programming Multi-core and Shared Memory Multiprocessors Using OpenMP (pp. 47–78)_ **in** _Introduction to Parallel Computing (Trobec et al., 2018)_

### 1. When run with one thread per logical core, threads from Listing 3.1 display their numbers randomly, while those from Listing 3.2 show them in the same order. Explain why.

The key difference between the two listings is the length of the operations. 

In Listing 3.1, the code executes the same, short operation on every thread: printing `omp_get_thread_num`. All threads are effectively competing to print to `stdout` at almost the same time, resulting in race conditions and (seemingly) random outputs.

In Listing 3.2, each thread computes a **different** Fibonacci number. Not only is this a longer operation that actually takes measurable time, but also the time is different for each thread: the Fibonacci number to compute depends on the thread id, where higher ids lead to higher calculation times. Now, prints to `stdout` happen after one another without race conditions.

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

#### 1. Solution:

The original code from lecture one can be found in `code/pi_monte_carlo_original.cpp`.

In the first step, I replaced the calculation of the number of points for each thread and the variable `counter_local` with a reduction operation. I also removed the explicitly atomic access to `counter`. The new simplified code can be seen in `code/pi_monte_carlo_reduction.cpp`, where `#pragma omp for reduction(+:counter)` is now used.

Next, I wanted to see how much of a difference the random number generator from the book makes. I modified `code/pi_monte_carlo_original.cpp` again, but this time kept `counter_local` and only added the new RNG function `rnd`. The code can be found in `code/pi_monte_carlo_better_rng.cpp`.

Lastly, I combined both the `reduction` clause and the new RNG into the final version, `code/pi_monte_carlo_modified.cpp`.

#### 2. Compilation:

```
> g++-15 -fopenmp pi_monte_carlo_original.cpp -o pi_monte_carlo_original
> g++-15 -fopenmp pi_monte_carlo_reduction.cpp -o pi_monte_carlo_reduction  
> g++-15 -fopenmp pi_monte_carlo_better_rng.cpp -o pi_monte_carlo_better_rng
> g++-15 -fopenmp pi_monte_carlo_modified.cpp -o pi_monte_carlo_modified
```

#### 3. Execution

```
>OMP_NUM_THREADS=8 ./pi_monte_carlo_original
Original Monte Carlo Simulation
pi: 3.14198
run_time: 1.25968 s
n: 100000000
> OMP_NUM_THREADS=8 ./pi_monte_carlo_reduction
Monte Carlo Simulation Using Reduction
pi: 3.14198
run_time: 1.22336 s
n: 100000000
> OMP_NUM_THREADS=8 ./pi_monte_carlo_better_rng
Monte Carlo Simulation With Better RNG
pi: 3.1416
run_time: 0.164094 s
n: 100000000
> OMP_NUM_THREADS=8 ./pi_monte_carlo_modified
Modified Monte Carlo Simulation
pi: 3.1416
run_time: 0.162063 s
n: 100000000
```

The original code has a run time of roughly 1.26 seconds. Switching to the `reduction` clause improved performance only marginally by approximately 0.036 seconds. I suppose that under the hood, the `reduction` clause uses very similar code as the explicit original version.

A much more significant improvement was achieved through the new random number generator. In my test, it shaved off almost 1.1 seconds of the original run time. That is a speedup of ~$7.68x$!

Adding the reduction clause to the code with the improved RNG function reduced the run time by another 0.002 seconds.

## Task 2 (optional)

**Do the coding warmup on slide 20**

### 1. Parallelize the serial π program (pi_numerical_integration.cpp) from the first lecture by adding only one extra line of code

Solution:
- See `code/pi_numerical_integration_parallelized.cpp`
- I added the line `#pragma omp parallel for reduction(+:sum)`

Execution:

```
> g++-15 -Ofast -std=c++11 -march=native -fopenmp pi_numerical_integration_original.cpp -o pi_numerical_integration_original
> g++-15 -Ofast -std=c++11 -march=native -fopenmp pi_numerical_integration_parallelized.cpp -o pi_numerical_integration_parallelized
> OMP_NUM_THREADS=8 ./pi_numerical_integration_original                                                                             
pi with 1000000000 steps is 3.1415926535900072 in 0.330346 seconds
> OMP_NUM_THREADS=8 ./pi_numerical_integration_parallelized                                         
pi with 1000000000 steps is 3.1415926535898078 in 0.07066 seconds
```
-> ~$4.68x$ speedup
-> through multiple runs, the parallelized code delivered consistent and approximately correct results, so lost updates do not seem to occur here ( = correct code :D )
