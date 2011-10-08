cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "-std=gnu++0x -O3 ${CMAKE_CXX_FLAGS}")
add_executable(pso pso.cpp)
