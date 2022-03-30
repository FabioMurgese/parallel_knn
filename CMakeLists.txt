cmake_minimum_required(VERSION 3.20)
project(parallel_knn)

set(CMAKE_CXX_STANDARD 14)

include_directories(/home/fabmoore/Documents/PDS/fastflow)

add_executable(parallel_knn
        knn_seq.cpp read_file.cpp)#utimer.cpp utils.cpp utils.h read_file.h read_file.cpp myqueue.cpp )
