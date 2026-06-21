# BreakOut

A small Breakout clone written in C++17, rendered with [SDL2](https://www.libsdl.org/).
The ball, paddle, and blocks are drawn from scratch onto a software pixel buffer
(Bresenham lines, polygon fill, double buffering) — no sprites or game engine.

## Controls

| Key       | Action                          |
| --------- | ------------------------------- |
| `A`       | Serve the ball / restart after game over |
| `←` / `→` | Move the paddle                 |

You start with three lives (shown as green circles in the bottom-left). Clear every
block to advance; lose all your lives and press `A` to start again.

## Prerequisites

- A C++17 compiler (GCC 8+, Clang 7+, or MSVC 2019+)
- [CMake](https://cmake.org/) 3.15 or newer
- SDL2 development libraries

Install SDL2:

```bash
# Debian / Ubuntu
sudo apt install libsdl2-dev

# Fedora
sudo dnf install SDL2-devel

# macOS (Homebrew)
brew install sdl2
```

## Build & run

```bash
cmake -S . -B build
cmake --build build
./build/break_out
```

## Running the tests

The pure geometry/math code lives in a window-free static library
(`breakout_logic`) that is unit tested with [doctest](https://github.com/doctest/doctest)
(vendored under `tests/doctest/`). The test target links that library only and needs
no SDL or display:

```bash
cmake --build build --target breakout_tests
ctest --test-dir build --output-on-failure
# or run the binary directly for richer output:
./build/breakout_tests
```

## Project layout

The build is split into three CMake targets:

- **`breakout_logic`** (static library) — `Utils/` (`Vec2D`, math helpers) and `Shapes/`
  (`AARectangle`, `Circle`, `Line2D`). Pure logic, no SDL dependency, fully unit tested.
- **`break_out`** (executable) — the game itself, linking `breakout_logic` and SDL2.
- **`breakout_tests`** (executable) — the doctest suite.

Source directories:

| Directory  | Responsibility                                                        |
| ---------- | --------------------------------------------------------------------- |
| `App/`     | Application object: window setup, scene stack, fixed-timestep loop.   |
| `Game/`    | Gameplay: `Breakout`, `Ball`, `Paddle`, `Block`, levels, collisions.  |
| `Scenes/`  | Scene abstraction (`MainScene`, `GameScene`).                         |
| `Input/`   | SDL event polling mapped to per-scene action callbacks.               |
| `Graphic/` | `Screen` / `ScreenBuffer` / `Color` — the software renderer.          |
| `Shapes/`  | Geometric primitives and intersection tests.                          |
| `Utils/`   | `Vec2D` vector math and float helpers.                                |

The `App` owns the game and injects the play-area boundary into each scene, so the
game logic has no global state and can be exercised without a window.

## License

Released under the [MIT License](LICENSE).
