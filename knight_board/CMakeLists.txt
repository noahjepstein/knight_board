project("Cruise: Knight Board")
cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Wextra -Werror")

include_directories(include)

add_executable(knight_board
                src/main.cpp
                src/board.cpp
                include/board.h)
