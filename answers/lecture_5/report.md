# Report on Exam Assignments - Lecture 5

## Task 1

**The program in quantpng.zip uses a Makefile for compilation. Add three CMakeLists.txt so that the program can be built with CMake.**

Solution: See `code/quantpng`

CMake commands:

```
cmake -DCMAKE_CXX_COMPILER=g++-15 -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel 11
```

Full execution log:

```
> quantpng % mkdir build
> quantpng % cd build 
> quantpng % cmake -DCMAKE_CXX_COMPILER=g++-15 -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_BUILD_TYPE=Release ..
-- The CXX compiler identification is GNU 15.2.0
-- The C compiler identification is GNU 15.2.0
-- Checking whether CXX compiler has -isysroot
-- Checking whether CXX compiler has -isysroot - yes
-- Checking whether CXX compiler supports OSX deployment target flag
-- Checking whether CXX compiler supports OSX deployment target flag - yes
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /opt/homebrew/bin/g++-15 - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Checking whether C compiler has -isysroot
-- Checking whether C compiler has -isysroot - yes
-- Checking whether C compiler supports OSX deployment target flag
-- Checking whether C compiler supports OSX deployment target flag - yes
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /opt/homebrew/bin/gcc-15 - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Found OpenMP_C: -fopenmp (found version "4.5")
-- Found OpenMP_CXX: -fopenmp (found version "4.5")
-- Found OpenMP: TRUE (found version "4.5")
-- Configuring done (1.7s)
-- Generating done (0.0s)
-- Build files have been written to: /algorithm-engineering/answers/lecture_5/code/quantpng/build
> build % cmake --build . --parallel 11
[  8%] Building C object quantize/CMakeFiles/quantize.dir/blur.c.o
[ 16%] Building C object quantize/CMakeFiles/quantize.dir/mediancut.c.o
[ 25%] Building C object quantize/CMakeFiles/quantize.dir/pam.c.o
[ 33%] Building CXX object lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o
[ 58%] Building C object quantize/CMakeFiles/quantize.dir/kmeans.c.o
[ 58%] Building C object quantize/CMakeFiles/quantize.dir/libimagequant.c.o
[ 58%] Building C object quantize/CMakeFiles/quantize.dir/nearest.c.o
[ 66%] Building C object quantize/CMakeFiles/quantize.dir/mempool.c.o
[ 75%] Linking C static library libquantize.a
[ 75%] Built target quantize
[ 83%] Linking CXX static library liblodepng.a
[ 83%] Built target lodepng
[ 91%] Building CXX object CMakeFiles/quantpng.dir/main.cpp.o
[100%] Linking CXX executable quantpng
[100%] Built target quantpng
> build % ./quantpng ../pluto.png 
Written quantized_example.png
```

## Task 2

**Create a static library that computes fizzbuzz. Test this static library using Catch2.**

Solution: See `code/test_fizzbuzz`

CMake commands:

```
cmake -DCMAKE_CXX_COMPILER=g++-15 -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel 11
```

Full execution log:

```
> test_fizzbuzz % mkdir build
> test_fizzbuzz % cd build 
> build % cmake -DCMAKE_CXX_COMPILER=g++-15 -DCMAKE_BUILD_TYPE=Release ..
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- The CXX compiler identification is GNU 15.2.0
-- Checking whether CXX compiler has -isysroot
-- Checking whether CXX compiler has -isysroot - yes
-- Checking whether CXX compiler supports OSX deployment target flag
-- Checking whether CXX compiler supports OSX deployment target flag - yes
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /opt/homebrew/bin/g++-15 - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
CMake Deprecation Warning at fizzbuzz/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


CMake Deprecation Warning at catch/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- Configuring done (0.6s)
-- Generating done (0.0s)
-- Build files have been written to: /algorithm-engineering/answers/lecture_5/code/test_fizzbuzz/build
> build % cmake --build . --parallel 11
[ 20%] Building CXX object fizzbuzz/CMakeFiles/fizzbuzz.dir/src/fizzbuzz.cpp.o
[ 40%] Linking CXX static library libfizzbuzz.a
[ 40%] Built target fizzbuzz
[ 80%] Building CXX object CMakeFiles/fizzbuzz_tests.dir/catch_tests_fizzbuzz.cpp.o
[ 80%] Building CXX object CMakeFiles/fizzbuzz_tests.dir/catch_main.cpp.o
[100%] Linking CXX executable fizzbuzz_tests
[100%] Built target fizzbuzz_tests
> build % ./fizzbuzz_tests 
===============================================================================
All tests passed (68 assertions in 3 test cases)
```