cmake_minimum_required(VERSION 4.0)
project(Libra)

set(CMAKE_CXX_STANDARD 14)

add_executable(Libra
        "src/Libra main.cpp"
        "Include/Libra main.h"
        src/menu.cpp
        Include/menu.h
        src/LoginAsAdmin.cpp
        Include/LoginAsAdmin.h)

