cmake_minimum_required(VERSION 3.20)
project(tic_tac_toe_analyser)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tic_tac_toe_analyser
        movedef.h
        tttanalyzer.cpp)
