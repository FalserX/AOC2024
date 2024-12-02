cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME AOC-2024-day-2)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES main.cpp FileOperations.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})