# Report on Exam Assignments - Lecture 6

## Task 1

**Name some characteristics of the instructions sets: SSE, AVX(2) and AVX-512.**

### SSE

- SSE = Streaming SIMD Extensions
- 16 Registers: xmm0 – xmm15 (128 bits)
- 70 new instructions compared to the original x86 ISA
- designed by Intel and introduced in 1999 in its Pentium III CPU series
- SSE was later expanded to SSE2, SSE3, SSSE3 and SSE4
- SSE originally supported only four 32-bits single-precision floating point numbers
- SSE2 expanded support to
    - two 64-bit double-precision floating-point numbers or
    - two 64-bit integers or
    - four 32-bit integers or
    - eight 16-bit short integers or
    - sixteen 8-bit bytes or characters.

### AVX(2)

- AVX = Advanced Vector Extensions
- Introduced in 2011 with Intel's Sandy Bridge and AMD's Bulldozer architectures
- AVX2 was introduced in 2013 with Intel's Haswell architecture and expanded integer support to 256 bits
- 16 Registers: ymm0 – ymm15 (256 bits)
- each YMM register can hold and do simultaneous operations (math) on:
    - eight 32-bit single-precision floating-point numbers or
    - four 64-bit double-precision floating-point numbers
- the legacy SSE instructions can still be utilized via the VEX prefix to operate on the lower 128 bits of the YMM registers

### AVX-512

- AVX-512 = Advanced Vector Extensions 512
- expands AVX to 512-bit support using a new EVEX prefix encoding proposed by Intel in 2013
- in conventional processors, AVX-512 was introduced with Skylake server and HEDT processors in 2017
- 32 Registers: zmm0 – zmm31 (512 bits)


## Task 2

**How can memory aliasing affect performance?**

Memory aliasing occurs when two or more pointers reference the same memory location. Since the compiler will only do safe optimizations when it is certain that no aliasing occurs, it may miss optimization opportunities. This may negatively affect performance.

A solution to this problem is to use the `restrict` keyword in C/C++. This keyword tells the compiler that the pointer is the only reference to that memory location, enabling a number of optimizations (including vectorization) that can improve performance.

## Task 3

**What are the advantages of unit stride (stride-1) memory access compared to accessing memory with larger strides (for example, stride-8)?**

Unit stride memory access means accessing consecutive memory locations without skipping any elements. This has several advantages:

- higher cache efficiency: unit stride access allows for better utilization of cache lines, reducing cache misses and thus improving performance
    - Example with 64-byte cache lines:
        - stride-1 access fetches 16 contiguous 4-byte floats
        - stride-8 access fetches only 8 floats, leaving half of the cache line unused
- improved vectorization: it is easier for compilers to apply SIMD (Single Instruction, Multiple Data) optimizations when data is accessed with unit stride
    - having stride-8 access may prevent the compiler from vectorizing loops, leading to slower execution

## Task 4

**When would you prefer arranging records in memory as a Structure of Arrays?**

A Structure of Arrays (SoA) is preferred when performing operations that involve a single field across many records. This can be explained with the following example:
- Consider a structure `a` representing a 3D point with fields `x`, `y`, and `z`.
- If we have an array of such structures and we want to perform operations on all `x` coordinates, accessing them in a SoA layout (i.e., separate arrays for `x`, `y`, and `z`) allows for better memory locality and vectorization.
    - This is because all `x` values are stored contiguously in memory: `a.x[0], a.x[1], a.x[2], ...`
    - Access to different values of a field can be done with unit stride, which is (as described in Task 3) beneficial for performance.
- If the Array of Structures (AoS) layout was used instead, accessing all `x` values would involve jumping through memory locations, leading to poor cache performance and hindering vectorization opportunities.
    - This is because the `x` values would be interleaved with `y` and `z` values: `a[0].x, a[0].y, a[0].z, a[1].x, a[1].y, a[1].z, ...`
    - Access to different values of a field would be done with a larger stride, which is less efficient.