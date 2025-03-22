cmake_minimum_required(VERSION 3.30)
project(SO2_Dining_philosophers)

set(CMAKE_CXX_STANDARD 20)

add_executable(SO2_Dining_philosophers src/main.cpp
        src/Philosopher.cpp
        src/Philosopher.h
        src/Semaphore.cpp
        src/Semaphore.h)

set_target_properties(SO2_Dining_philosophers PROPERTIES OUTPUT_NAME "philosophers")
