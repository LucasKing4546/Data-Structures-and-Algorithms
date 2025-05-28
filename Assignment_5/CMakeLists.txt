cmake_minimum_required(VERSION 3.30)
project(Assignment_5)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment_5 App.cpp ExtendedTest.cpp
               ExtendedTest.h ShortTest.cpp ShortTest.h
                Matrix.cpp Matrix.h)
