cmake_minimum_required(VERSION 3.29)
project(src C)

set(CMAKE_C_STANDARD 11)

add_executable(src main.c
        Labirinto.c
        Estudante.c
        Estudante.h)
