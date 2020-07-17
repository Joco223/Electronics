cmake_minimum_required(VERSION 3.10)

project(Electronics VERSION 0.1)

include_directories(include)
file(GLOB SOURCES "source/*.cpp")

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-O3 -ffast-math -march=native")

#Executable
add_executable(Electronics ${SOURCES})