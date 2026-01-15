# Report on Exam Assignments - Lecture 12

## Task 1

**Select three slides from the lecture, research more about the topics, and report on them.**

### Slide 11

The first slide I would like to talk about is slide 11 "Memory-Mapped Files to Abstract IO Away". The slide shows a code snippet that demonstrates how to use memory-mapped files in C++ on Linux. Before going into the code, I'd first like to recap what memory-mapped files are. Memory-mapped files allow applications to access files on disk as if they were part of the virtual memory. Essentially (this is a translated quote from the lecture), “a file is opened and interpreted as a single large C/C++ array.” This can lead to performance improvements because it reduces the number of system calls required for file I/O operations. Instead of reading and writing data through traditional file I/O functions, applications can directly read from and write to memory.

The code snippet describes a procedure of opening a 1GB random data file, inverting all bytes, and writing the result back to disk. To create a memory-mapping, the code uses the `mmap64` system call, which maps a file into the process's address space and returns a pointer to the start of the mapped region. The `mmap64` function takes several parameters, including the desired memory address (set to `nullptr` to let the system choose), the length of the mapping (in bytes), protection flags (read and write), mapping flags (shared mapping), file descriptor, and offset (0 for the start of the file). In this example, the input file is mapped with `PROT_READ`, meaning it is read-only, and `MAP_SHARED`, which allows changes to be visible to other processes if the mapping were writable.
Next, the code opens an output file using `open64` with read-write access and `-rw-rw-r--` permissions. It then uses `fallocate64` to allocate enough space for the output file to match the size of the input file. After that, `mmap64` is called again to create a memory-mapping for the output file but this time using `PROT_WRITE | PROT_READ`. The code then iterates through each byte of the input mapping, inverts it by subtracting it from `255`, and writes the result to the output mapping.  From the developer's perspective, this process is the same as editing two arrays in memory, without having to explicitly manage low-level file I/O operations. Finally, the input mapping is unmapped using `munmap`, and the output mapping is synchronized to disk using `msync` before being unmapped as well. The `MS_ASYNC` flag indicates that the synchronization may be performed asynchronously.

Note: The code snippet uses the 64-bit versions of the functions (`mmap64`, `open64`, `fallocate64`) to support large files (over 4GB).

### Slide 13

The second slide for which I did further research is slide 13 "General-Purpose Computing on Graphics Processing Units". This slide introduces a few frameworks for GPU programming, such as OpenCL, CUDA, Metal, OpenACC and SYCL. Because I use a Macbook, I decided to look more into Metal, which is Apple's framework for GPU programming. Metal provides low-level access to the GPU, allowing developers to write highly optimized code for graphics rendering and general-purpose computing tasks. When writing code for Metal, developers can choose between `metal-cpp`, which is a C++ API, or the original `Metal Shading Language (MSL)`, which is a variant of C++ designed for GPU programming. Fortunately, Apple provides a lot of documentation and sample code for Metal on their developer website. Since the slide shows an OpenCL example of adding two vectors on the GPU, I looked for a similar example in Metal:


First, lets define the function in simple C:

```c
void vadd(const float* a, const float* b, float* c, int n)
{
    for (int index = 0; index < n ; index++)
    {
        c[index] = a[index] + b[index];
    }
}
```

Next, here is how the same function can be implemented in Metal Shading Language:

```metal
kernel void vadd(device const float* a, device const float* b, device float* c, uint index [[thread_position_in_grid]])
{
    // the for-loop is replaced with a collection of threads, each of which calls this function.
    c[index] = a[index] + b[index];
}
```

In the MSL example, the function adds the kernel keyword, which declares that the function is:
- A public GPU function. In an app, public functions are the only ones that can be called from the app (CPU side). Furthermore, other shader functions cannot call public functions.
- A compute function (also known as a compute kernel), which performs a parallel calculation using a grid of threads.

We can also see that the function parameters are decorated with the device address space qualifier, which indicates that the pointers refer to memory located on the GPU device. Finally, the index parameter is decorated with the thread_position_in_grid attribute, which provides each thread with its unique index within the grid of threads. The GPU automatically calculates this index based on the thread's position in the grid and calls the kernel function for each thread.

In conclusion, it seems that Metal is very similar to OpenCL when comparing the syntax of the two code snippets. Without looking deeper into the OpenCL specification, I would assume that the `__global` qualifier in OpenCL is equivalent to the `device` qualifier in Metal, and that the `get_global_id(0)` function in OpenCL is equivalent to the `thread_position_in_grid` attribute in Metal. Why reinvent the wheel? :)

Sources
- https://developer.apple.com/documentation/metal/
- https://developer.apple.com/documentation/metal/performing-calculations-on-a-gpu
