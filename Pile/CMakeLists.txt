cmake_minimum_required(VERSION 3.22)
project(Pile)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Pile
        exceptions.h
        pila.h
        pilapt.h
        pilavt.h
        tester.cpp)
