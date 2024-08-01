cmake_minimum_required(VERSION 3.27)
project(project2 C)

set(CMAKE_C_STANDARD 99)

add_executable(project2 main.c
        field.c
        auxiliary.c
        linklist.c
        menu.c
        menu.h
        sounds.c
        sounds.c
        sounds.h
)
