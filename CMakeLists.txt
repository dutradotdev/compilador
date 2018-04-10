cmake_minimum_required(VERSION 3.9)
project(compilador)

set(CMAKE_CXX_STANDARD 11)

add_executable(compilador
        nbproject/private/c_standard_headers_indexer.c
        nbproject/private/cpp_standard_headers_indexer.cpp
        analisador.h
        main.c
        stdLibList.h)
