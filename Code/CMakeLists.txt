cmake_minimum_required(VERSION 3.22)
project(Code)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Code
        codapt.h
        codavt.h
        tester.cpp coda.h)
