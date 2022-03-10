cmake_minimum_required(VERSION 3.20)
project(parallel_knn)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(parallel_knn
        utimer.cpp utils.cpp utils.h create_input_file.cpp read_file.h read_file.cpp knn_stl.cpp)
