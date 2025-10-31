# Report on Exam Assignments - Lecture 2

## Task 1

**What causes false sharing? Describe it visually by creating your own graphic.**

![False Sharing Graphic](./false_sharing_diagram.jpg)

## Task 2

**Read the paper There’s plenty of room at the Top: What will drive computer performance after Moore’s law? Explain in detail the figure Performance gains after Moore’s law ends.**

## Task 3 (optional)

**Do the coding warmup on slide 20.** 

### 1. Fix the race condition bug on page 13 with a std::mutex.

Solution: See `code/fixed_race_condition.cpp`

Execution:

```
> g++-15 -fopenmp fixed_race_condition.cpp -o fixed_race_condition
> ./fixed_race_condition                                          
pi with 1000000000 steps is 3.1415926535897687 in 0.379128 seconds
```

### 2. Reduce the runtime of the image denoising program on slide 16 by adding an appropriate schedule.

Instead of statically giving each thread the same number of loop iterations (default), this can be done dynamically during runtime using `schedule(dynamic)`.

Solution: See `code/unbalanced_workload.cpp` and `code/fixed_unbalanced_workload.cpp`.

Execution:

```
> g++-15 -fopenmp unbalanced_workload.cpp -o unbalanced_workload.o   
> g++-15 -fopenmp fixed_unbalanced_workload.cpp -o fixed_unbalanced_workload.o
> ./unbalanced_workload.o 
0.509375 seconds
> ./fixed_unbalanced_workload.o 
0.236174 seconds
```

The code is now a little over 2.1 times faster!

### 3. What schedule on slide 18 produces the following (bad) pattern?

## Task 4

**Rewrite the program for estimating π from the last lecture (pi_numerical_integration.cpp) so that it is parallelized with the #pragma omp for construct.**

Solution: See `code/pi_numerical_integration.cpp`

Execution:

```
> g++-15 -fopenmp pi_numerical_integration.cpp -o pi_numerical_integration  
> ./pi_numerical_integration
pi with 1000000000 steps is 3.1415926535896603 in 0.226869 seconds
```