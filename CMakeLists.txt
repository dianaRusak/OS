cmake_minimum_required(VERSION 3.15)
project(untitled2 C)

set(CMAKE_C_STANDARD 99)
set(PROJECT untitled2)

project(${PROJECT})

set(SOURCES main.c)

add_executable(${PROJECT} ${HEADERS} ${SOURCES})
