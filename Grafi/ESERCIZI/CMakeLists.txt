cmake_minimum_required(VERSION 3.24)
project(ESERCIZI)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(ESERCIZI
        graph_color.h
        tester.cpp one_label_path.h graph_path.h)
