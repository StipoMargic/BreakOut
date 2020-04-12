cmake_minimum_required(VERSION 3.15)
project(break_out)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} Utils Graphic)

add_executable(break_out
        main.cpp Graphic/Color.cpp Graphic/Color.hpp Utils/Vec2D.cpp Utils/Utils.cpp Utils/Vec2D.hpp Utils/Vec2D.cpp Utils/ScreenBuffer.cpp Utils/ScreenBuffer.hpp)

target_link_libraries(break_out ${SDL2_LIBRARIES} )