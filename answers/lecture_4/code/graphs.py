import matplotlib.pyplot as plt

threads_numbers_data = list(range(1,12))
threads_quicksort_speedup_data = [0.83951, 1.53795, 2.1567, 2.66135, 3.12509, 3.53431, 3.71147, 4.04133, 4.22122, 4.43891, 4.59407]
threads_gnu_parallel_sort_speedup_data = [0.99706, 1.87928, 2.64885, 3.60776, 3.96222, 4.59522, 5.10908, 6.06171, 6.30018, 6.75963, 7.36908]

f1 = plt.figure()
plt.plot(threads_numbers_data, threads_quicksort_speedup_data, label='Quicksort Speedup', marker='o')
plt.plot(threads_numbers_data, threads_gnu_parallel_sort_speedup_data, label='GNU Parallel Sort Speedup', marker='o')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.title('Speedup of Quicksort and GNU Parallel Sort over std::sort')
plt.legend()
plt.grid(True)
plt.savefig('../speedup_vs_threads.png')

arrays_sizes_data = [100000, 1000000, 10000000, 100000000, 1000000000]
arrays_quicksort_speedup_data = [3.3068, 4.25359, 4.52912, 4.47268, 3.6756]
arrays_gnu_parallel_sort_speedup_data = [3.62078, 6.01144, 6.61574, 6.9667, 4.51434]

f2 = plt.figure()
plt.plot(arrays_sizes_data, arrays_quicksort_speedup_data, label='Quicksort Speedup', marker='o')
plt.plot(arrays_sizes_data, arrays_gnu_parallel_sort_speedup_data, label='GNU Parallel Sort Speedup', marker='o')
plt.xlabel('Array Size')
plt.ylabel('Speedup')
plt.title('Speedup of Quicksort and GNU Parallel Sort over std::sort')
plt.xscale('log')
plt.legend()
plt.grid(True)
plt.savefig('../speedup_vs_array_size.png')