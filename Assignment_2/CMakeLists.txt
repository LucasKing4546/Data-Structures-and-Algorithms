cmake_minimum_required(VERSION 3.30)
project(Assignment_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment_2 MultiMap.cpp MultiMap.h MultiMapIterator.h MultiMapIterator.cpp App.cpp
        ExtendedTest.cpp ExtendedTest.h ShortTest.cpp ShortTest.h)
