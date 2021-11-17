cmake_minimum_required(VERSION 3.20)
project(Jezyk_z_czasem)

set(CMAKE_CXX_STANDARD 14)

add_executable(tln
        sources/main.cpp
        sources/CodeSource.cpp
        headers/CodeSource.h
        headers/CharAndPosition.h)
