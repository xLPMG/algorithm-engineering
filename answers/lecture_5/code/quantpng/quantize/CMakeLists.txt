cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(quantize LANGUAGES C)

find_package(OpenMP REQUIRED)

add_library(quantize STATIC
    blur.c
    blur.h
    kmeans.c
    kmeans.h
    libimagequant.c
    libimagequant.h
    mediancut.c
    mediancut.h
    mempool.c
    mempool.h
    nearest.c
    nearest.h
    pam.c
    pam.h
)

target_link_libraries(quantize PUBLIC OpenMP::OpenMP_CXX)