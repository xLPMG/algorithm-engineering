cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(lodepng LANGUAGES CXX)

add_library(lodepng STATIC
    lodepng.cpp
    lodepng.h
)