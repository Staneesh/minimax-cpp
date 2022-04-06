cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(minimax-cpp)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(minimax-cpp src/main.cpp src/game.cpp)

target_include_directories(minimax-cpp PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )