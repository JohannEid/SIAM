cmake_minimum_required(VERSION 3.6)
project(SIAM02)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Object.cpp Object.h Header.h Player.cpp Player.h Board.cpp Board.h "Player sub_methods.cpp" "Player sub_methods.h" global.h "utilities .h" utilities.cpp Header.cpp)
add_executable(SIAM02 ${SOURCE_FILES})