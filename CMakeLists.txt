cmake_minimum_required(VERSION 3.6.3)
project(sort C)

set(CMAKE_C_STANDARD 99)

add_executable(sort sort.c)
add_executable(heap heap.c)
add_executable(bst bst.c)
add_executable(backtracking backtracking.c)
add_executable(dynamic dynamic.c)