cmake_minimum_required(VERSION 3.20)
project(Jezyk_z_czasem)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/doctest)
add_subdirectory(src/)
add_subdirectory(tests/)