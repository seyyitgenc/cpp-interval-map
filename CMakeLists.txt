cmake_minimum_required(VERSION 3.5)

project(task-thinkcell CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -O0")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)
