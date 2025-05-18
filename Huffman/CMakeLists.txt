cmake_minimum_required(VERSION 3.30)
project(Huffman)

set(CMAKE_CXX_STANDARD 20)

add_executable(Huffman_encoder
        define.h
        node.h
        node.cpp
        code.h
        code.cpp
        huffman.h
        huffman.cpp
        io.h
        io.cpp
        encoder.cpp)

add_executable(Huffman_decoder
        define.h
        node.h
        node.cpp
        code.h
        code.cpp
        huffman.h
        huffman.cpp
        io.h
        io.cpp
        decoder.cpp)
