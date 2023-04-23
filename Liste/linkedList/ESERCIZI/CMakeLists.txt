cmake_minimum_required(VERSION 3.24)
project(ESERCIZI)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(ESERCIZI
        rating.h
        tester.cpp ../linkedList.h)
