cmake_minimum_required(VERSION 3.22)
project(Dizionari)

set(CMAKE_C_STANDARD 14)

include_directories(.)

add_executable(
        dictionary.h
        hash_table.h
        tester.cpp)
