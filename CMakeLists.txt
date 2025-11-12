cmake_minimum_required(VERSION 3.31)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(program3 main.cpp
        list342.h
        child.cpp
        child.h)
