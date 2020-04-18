cmake_minimum_required(VERSION 3.15)
project(break_out)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} Utils Graphic Shapes App Scenes Input Game)

add_executable(break_out
        main.cpp Graphic/Color.cpp Graphic/Color.hpp Utils/Vec2D.cpp Utils/Utils.cpp Utils/Vec2D.hpp Utils/Vec2D.cpp Graphic/ScreenBuffer.cpp Graphic/ScreenBuffer.hpp Graphic/Screen.cpp Graphic/Screen.hpp Shapes/Line2D.cpp Shapes/Line2D.hpp Shapes/Shape.cpp Shapes/Shape.hpp Shapes/AaRectangle.cpp Shapes/AaRectangle.hpp Shapes/Circle.cpp Shapes/Circle.hpp App/App.cpp App/App.hpp Scenes/Scene.hpp Scenes/MainScene.cpp Scenes/MainScene.hpp Input/GameController.cpp Input/GameController.hpp Input/InputController.cpp Input/InputController.hpp Game/Game.hpp Scenes/GameScene.cpp Scenes/GameScene.hpp Game/Breakout.cpp Game/Breakout.hpp Game/Excluder.cpp Game/Excluder.hpp Game/BoundaryEdge.hpp Game/Paddle.cpp Game/Paddle.hpp)

target_link_libraries(break_out ${SDL2_LIBRARIES})