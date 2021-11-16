cmake_minimum_required(VERSION 3.20)
project(List)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(List
        include/List.h
        src/List_General_Func.cpp
        src/List_Main.cpp
        src/List_Dump.cpp
        src/List_Test.cpp
        src/List_Error_Check.cpp
        src/List_Insert_Func.cpp
        src/List_Delete_Func.cpp
        src/List_Get_Func.cpp)
