cmake_minimum_required(VERSION 3.15)
project(break_out VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/sdl/")

# ---------------------------------------------------------------------------
# breakout_logic: pure, window-free code (no SDL dependency).
# This is the part that can be unit tested without a graphics context.
# ---------------------------------------------------------------------------
add_library(breakout_logic STATIC
        Utils/Vec2D.cpp
        Utils/Utils.cpp
        Shapes/Shape.cpp
        Shapes/Line2D.cpp
        Shapes/AaRectangle.cpp
        Shapes/Circle.cpp)
target_include_directories(breakout_logic PUBLIC Utils Shapes)

# ---------------------------------------------------------------------------
# break_out: the game executable (SDL window, input, rendering, game loop).
# ---------------------------------------------------------------------------
find_package(SDL2 REQUIRED)

add_executable(break_out
        main.cpp
        Graphic/Color.cpp
        Graphic/ScreenBuffer.cpp
        Graphic/Screen.cpp
        App/App.cpp
        Scenes/MainScene.cpp
        Scenes/GameScene.cpp
        Input/GameController.cpp
        Input/InputController.cpp
        Game/Breakout.cpp
        Game/Excluder.cpp
        Game/Paddle.cpp
        Game/Ball.cpp
        Game/LevelBoundary.cpp
        Game/Block.cpp
        Game/GameLevel.cpp)
target_include_directories(break_out PRIVATE ${SDL2_INCLUDE_DIRS} Graphic App Scenes Input Game)
target_link_libraries(break_out PRIVATE breakout_logic ${SDL2_LIBRARIES})

# ---------------------------------------------------------------------------
# breakout_tests: unit tests for the logic library (links breakout_logic only,
# no SDL). Run with `ctest` or by invoking the binary directly.
# ---------------------------------------------------------------------------
enable_testing()

add_executable(breakout_tests
        tests/test_main.cpp
        tests/test_vec2d.cpp
        tests/test_utils.cpp
        tests/test_aarectangle.cpp
        tests/test_circle.cpp
        tests/test_line2d.cpp)
target_include_directories(breakout_tests PRIVATE tests/doctest)
target_link_libraries(breakout_tests PRIVATE breakout_logic)

add_test(NAME breakout_tests COMMAND breakout_tests)
