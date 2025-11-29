cmake_minimum_required(VERSION 4.0)
project(Libra)

set(CMAKE_CXX_STANDARD 14)

add_executable(Libra
        "Libra main.cpp"
        "Libra main.h"
        menu.cpp
        menu.h)

