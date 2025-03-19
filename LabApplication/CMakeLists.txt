cmake_minimum_required(VERSION 3.30)
project(LabApplication)

set(CMAKE_CXX_STANDARD 20)

add_executable(LabApplication
        App.cpp
        ExtendedTest.cpp
        FixedCapBiMap.cpp
        FixedCapBiMapIterator.cpp
        ShortTest.cpp
)
