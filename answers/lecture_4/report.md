# Report on Exam Assignments - Lecture 4

## Task 1

**Benchmark min_max_quicksort against std::sort and __gnu_parallel::sort. (you can adjust min_max_quicksort.cpp as necessary)**

### 1. Provide details of your benchmarking environment.

- Operating System: MacOS 26.1
- RAM: LPDDR5-6400 36GB unified memory (shared between CPU and GPU)
- CPU: 
    - Apple M3 Pro
    - 5 performance CPU cores; 0.70 to 4.06 GHz;
    - 6 efficiency CPU cores; 0.74 to 2.75 GHz;
    - L1 cache:
        - P-Cores: 192 + 128 KiB per core
        - E-Cores: 128 + 64 KiB per core
    - L2 cache:
        - P-Cores: 16 MiB
        - E-Cores: 4 MiB
- Compiler: g++-15 (Homebrew GCC 15.2.0) 15.2.0

### 2. Create a graph where the x-axis represents the number of threads and the y-axis displays the relative speedup over std::sort.

Solution: See `code/min_max_quicksort_threads.cpp`

Execution:

```
> g++-15 -fopenmp -march=native -Ofast min_max_quicksort_threads.cpp -o min_max_quicksort_threads     
> ./min_max_quicksort_threads 
Benchmarking with 1 threads:
  std::sort time: 5.60108 s
  min_max_quicksort time: 6.67184 s
  speedup over std::sort: 0.83951
  __gnu_parallel::sort time: 5.6176 s
  speedup over std::sort: 0.99706
Benchmarking with 2 threads:
  std::sort time: 5.58609 s
  min_max_quicksort time: 3.63217 s
  speedup over std::sort: 1.53795
  __gnu_parallel::sort time: 2.97246 s
  speedup over std::sort: 1.87928
Benchmarking with 3 threads:
  std::sort time: 5.6435 s
  min_max_quicksort time: 2.61673 s
  speedup over std::sort: 2.1567
  __gnu_parallel::sort time: 2.13055 s
  speedup over std::sort: 2.64885
Benchmarking with 4 threads:
  std::sort time: 5.75403 s
  min_max_quicksort time: 2.16207 s
  speedup over std::sort: 2.66135
  __gnu_parallel::sort time: 1.5949 s
  speedup over std::sort: 3.60776
Benchmarking with 5 threads:
  std::sort time: 5.72041 s
  min_max_quicksort time: 1.83048 s
  speedup over std::sort: 3.12509
  __gnu_parallel::sort time: 1.44374 s
  speedup over std::sort: 3.96222
Benchmarking with 6 threads:
  std::sort time: 5.74047 s
  min_max_quicksort time: 1.62421 s
  speedup over std::sort: 3.53431
  __gnu_parallel::sort time: 1.24923 s
  speedup over std::sort: 4.59522
Benchmarking with 7 threads:
  std::sort time: 5.73964 s
  min_max_quicksort time: 1.54646 s
  speedup over std::sort: 3.71147
  __gnu_parallel::sort time: 1.12342 s
  speedup over std::sort: 5.10908
Benchmarking with 8 threads:
  std::sort time: 5.77042 s
  min_max_quicksort time: 1.42785 s
  speedup over std::sort: 4.04133
  __gnu_parallel::sort time: 0.951945 s
  speedup over std::sort: 6.06171
Benchmarking with 9 threads:
  std::sort time: 5.80416 s
  min_max_quicksort time: 1.375 s
  speedup over std::sort: 4.22122
  __gnu_parallel::sort time: 0.921269 s
  speedup over std::sort: 6.30018
Benchmarking with 10 threads:
  std::sort time: 5.81588 s
  min_max_quicksort time: 1.3102 s
  speedup over std::sort: 4.43891
  __gnu_parallel::sort time: 0.860385 s
  speedup over std::sort: 6.75963
Benchmarking with 11 threads:
  std::sort time: 5.80396 s
  min_max_quicksort time: 1.26336 s
  speedup over std::sort: 4.59407
  __gnu_parallel::sort time: 0.78761 s
  speedup over std::sort: 7.36908
```

### 3. Construct another graph with the x-axis denoting the array size and the y-axis illustrating the relative speedup over std::sort.

```
> g++-15 -fopenmp -march=native -Ofast min_max_quicksort_array_sizes.cpp -o min_max_quicksort_array_sizes
> ./min_max_quicksort_array_sizes 
Benchmarking with array size 100000:
  std::sort time: 0.0037142 s
  min_max_quicksort time: 0.0011232 s
  speedup over std::sort: 3.3068
  __gnu_parallel::sort time: 0.0010258 s
  speedup over std::sort: 3.62078
Benchmarking with array size 1e+06:
  std::sort time: 0.042359 s
  min_max_quicksort time: 0.0099584 s
  speedup over std::sort: 4.25359
  __gnu_parallel::sort time: 0.0070464 s
  speedup over std::sort: 6.01144
Benchmarking with array size 1e+07:
  std::sort time: 0.518301 s
  min_max_quicksort time: 0.114438 s
  speedup over std::sort: 4.52912
  __gnu_parallel::sort time: 0.0783436 s
  speedup over std::sort: 6.61574
Benchmarking with array size 1e+08:
  std::sort time: 5.55762 s
  min_max_quicksort time: 1.24257 s
  speedup over std::sort: 4.47268
  __gnu_parallel::sort time: 0.79774 s
  speedup over std::sort: 6.9667
Benchmarking with array size 1e+09:
  std::sort time: 65.737 s
  min_max_quicksort time: 17.8847 s
  speedup over std::sort: 3.6756
  __gnu_parallel::sort time: 14.5618 s
  speedup over std::sort: 4.51434
```

### 4. Explain any patterns or trends observed in the graphs, and offer potential reasons for these findings.

## Task 2

**Read** _What every systems programmer should know about concurrency._ **Discuss two things you find particularly interesting.**