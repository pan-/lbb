cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project("Lightweight building blocks")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_NAME "lbb")

add_subdirectory(src)
