cmake_minimum_required(VERSION 3.24)
project(cppstr)

set(CMAKE_CXX_STANDARD 11)

add_executable(cppstr_tests cppstr.hpp tests.cpp)
add_executable(example cppstr.hpp example.cpp)

