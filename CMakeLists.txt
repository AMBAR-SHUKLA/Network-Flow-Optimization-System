cmake_minimum_required(VERSION 3.10)
project(NetworkFlowSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fopenmp")

include_directories(src/engine)

add_library(engine STATIC
    src/engine/graph.hpp
    src/engine/push_relabel.cpp
    src/engine/gomory_hu.cpp
)
