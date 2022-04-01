cmake_minimum_required(VERSION 3.17)
project(simplex_table VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(simplex_table main.cpp SimplexTable.cpp SimplexTable.h Fraction.cpp Fraction.h)