# Report on Exam Assignments - Lecture 1

Some remarks:
- Whenever I use an LLM or Code Agent, I will specify so
- To keep the repository size small, I will not include binary executables. However, (whenever it seems necessary,) I will include the commands which I used to compile

## Task 1

**Select one slide from the lecture, research more about the topic, and report on it.**

For this task, I researched more about what OpenMP is and how it functions. This research extends the information presented on slide 11 of the lecture slides.

OpenMP is an application programming interface (API) designed for developing shared memory parallel applications in C, C++, and Fortran. Its specification is maintained by the OpenMP Architecture Review Board, and the most recent official release is version 6.0 (November 2024). Before examining how OpenMP works, I would like to address the question of when OpenMP should be used.

Although the GCC compiler is already capable of automatically parallelizing code ([source](https://gcc.gnu.org/wiki/AutoParInGCC)), there are limitations that make OpenMP valuable. Automatic parallelization faces two main challenges. First, the compiler may not be able to identify code that can safely be parallelized. Analyzing data dependencies and ensuring that parallel execution does not alter program results is not a trivial task and the compiler may choose sequential execution instead, even when parallel execution is theoretically possible. Second, the level of granularity achieved through automatic parallelization may be not high enough. The compiler often lacks contextual information about the structure and intent of the application, which limits its ability to parallelize at the highest possible level. OpenMP helps solve these problems, as it enables manual and explicit parallelization. This allows the programmer to choose exactly where and how the code should be parallelized. If done right, higher performance than automatic parallelization can be achieved.

The OpenMP specification uses the Fork and Join Model, as shown on slide 13. Simply explained, an OpenMP parallelized program is started using a master thread, and whenever a parallel region is encountered, the master thread spawns additional worker threads (forking) that help process the parallel region. When all threads have completed their tasks, the worker threads are synchronized and joined, so that only the master thread remains to continue execution. 

To ensure that such a system works in practice, the OpenMP Memory Model specifies how threads can access memory regions. Each thread that is spawned has access to the same, globally shared, memory of the application. This allows for usage of shared data, of which there is only one instance that is accessible by all threads. Unless protected through a specific OpenMP construct, shared data can be read and written by all threads simultaneously. The memory model also specifies that each thread has its own private memory region to handle private data. Here, each thread has its own copy and other threads can't access this data.

Main source: https://www.openmp.org/wp-content/uploads/ntu-vanderpas.pdf

## Task 2

**Read Chapter 1 from Computer Systems: A Programmer’s Perspective. Discuss two things you find particularly interesting.**

Link: http://csapp.cs.cmu.edu/2e/ch1-preview.pdf

What I found most interesting, was that files are used as an abstraction of I/O devices. I had previously heard that on Windows systems, there are reserved file names that may not be chosen by the user when creating files, because the operating system uses them to interact with devices. These include for example `CON` for writing text to the console and `PRN` for sending text to a printer device. When I heard about this, I thought it was just an odd quirk that was [specific to DOS/Windows](https://en.wikipedia.org/wiki/DOS#File_system). Surprisingly, as the book mentions, modeling all devices as files is a fundamental abstraction to Unix and Unix-like operating systems. This inspired me to research more about this topic, as the book does not really go into detail. During this research, I found a comprehensive list of 'device files' for Linux [here](https://tldp.org/LDP/Linux-Filesystem-Hierarchy/html/dev.html) and also found out that [MS-DOS actually borrowed the concept of using files as an abstraction for I/O devices from Unix](https://en.wikipedia.org/wiki/Device_file). Personally, I think this is a very elegant way of interacting with devices. It allows programmers to use the same `read()` and `write()` system calls for all I/O operations, regardless of the underlying hardware. This abstraction means programmers don't need to worry about the specifics of each device, because at a high level, it appears just like a regular file. However, under the hood, the device drivers handle the hardware details. Very cool!

The second excerpt that I found interesting was the `Aside: The Linux project` section. It shows an e-mail written by Linux Torvalds, talking about his hobby-project `minix`. With this, Torvalds laid out the foundation for the Linux operating system. I find it remarkable, that a single university student can take on such a project all by himself. In today's age, there are tons of tutorials and video material on how to code simple operating systems. Torvalds e-mail however dates back to 1991, the same year the [World Wide Web was just published](https://en.wikipedia.org/wiki/World_Wide_Web). All his knowledge must have come from his classes or books that he read in his free time.

## Task 3 (optional)

**Do the coding warmup on slide 19**

### 1. Compile and run the programs of slides 12 and 14

Slide 12:

```
> g++-15 -fopenmp hello.cpp -o hello                    
> OMP_NUM_THREADS=4 ./hello
Hello from thread Hello from thread Hello from thread Hello from thread 3021
```

Slide 14 OpenMP:

```
> g++-15 -fopenmp hello_simple.cpp -o hello_simple
> OMP_NUM_THREADS=4 ./hello_simple          
Hello World!Hello World!

Hello World!
Hello World!
```

Slide 14 Generated:

```
> g++-15 generated.cpp -o generated
> ./generated
Hello World!
Hello World!Hello World!

Hello World!
```

### 2. Create a parallel version of the π program (slide 16)

Since we already implemented this during class, I decided to take `code/pi_openmp_v1.cpp` and try to improve it. For this, I also used the help of an LLM (Github Copilot). The resulting code uses the `for reduction` directive and the code can be seen in `code/pi_openmp_v2.cpp`.

### 3. Watch the times your implementation needs with different numbers of threads

| Number of Threads | Exec Time V1 (s) | Exec Time V2 (s) |
|-------------------|-------------------|-----------------|
| 1                 | 1.34119           | 1.32051         |
| 4                 | 0.380749          | 0.375255        |
| 8                 | 0.344282          | 0.257448        |

We can see that increasing the number of threads reduced execution time and also the optimized code V2 (from task 2) was faster than V1 in all cases.

### 4. Try compiling with optimization flag -Ofast

| Number of Threads | V2 - no Ofast (s) | V2 - with Ofast (s) |
|-------------------|-------------------|---------------------|
| 1                 | 1.32051           | 0.331025            |
| 4                 | 0.375255          | 0.098168            |
| 8                 | 0.257448          | 0.070925            |

Compiling with -Ofast decreased the execution times by a lot! I'm honestly surprised :D

## Task 4

**Parallelize the program of slide 21 with OpenMP.**

Solution: See `code/pi_monte_carlo.cpp`

Execution:
```
> g++-15 -fopenmp pi_monte_carlo.cpp -o pi_monte_carlo
> OMP_NUM_THREADS=1 ./pi_monte_carlo
pi: 3.14176
run_time: 6.65308 s
n: 100000000
> OMP_NUM_THREADS=11 ./pi_monte_carlo          
pi: 3.14185
run_time: 1.03814 s
n: 100000000
```