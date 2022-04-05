cmake_minimum_required(VERSION 3.17)
project(Simplex-Table VERSION 1.2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        ./src/main.cpp
        ./src/SimplexTable/SimplexTable.cpp
        ./src/SimplexTable/SimplexTable.h
        ./src/Fraction/Fraction.cpp
        ./src/Fraction/Fraction.h
        )