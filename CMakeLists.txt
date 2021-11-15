cmake_minimum_required(VERSION 3.20)
project(List)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(List
        include/List.h
        src/ListFunc.cpp
        src/ListMain.cpp
        src/ListDump.cpp
        src/ListTest.cpp
        src/ListErrorCheck.cpp)
