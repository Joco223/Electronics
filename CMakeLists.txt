cmake_minimum_required(VERSION 3.10)

project(Electronics VERSION 0.1)

find_package(Lua 5.3 REQUIRED)

include_directories(include ${LUA_INCLUDE_DIR})
file(GLOB SOURCES "source/*.cpp")

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-O3 -ffast-math -march=native")
set(CMAKE_CXX_FLAGS "-O3 -ffast-math -march=native")

#Executable
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Electronics ${SOURCES})
target_link_libraries(Electronics sfml-graphics sfml-audio ${LUA_LIBRARIES})
