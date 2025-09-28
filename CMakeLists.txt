cmake_minimum_required(VERSION 3.28.3)
project(Sdb C)

set(CMAKE_C_STANDARD 11)

add_executable(Sdb main.c
        test/test_db.cpp)
