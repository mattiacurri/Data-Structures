cmake_minimum_required(VERSION 3.24)
project(Parentesi_bilanciate)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Parentesi_bilanciate
        bilanciate.h
        tester.cpp)
