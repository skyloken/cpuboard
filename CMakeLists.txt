cmake_minimum_required(VERSION 3.10)
project(cpu C)

set(CMAKE_C_STANDARD 99)

add_executable(cpu src/main.c src/cpuboard.c src/cpuboard.h src/instruction.c)