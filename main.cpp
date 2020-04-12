#include <SDL2/SDL.h>
#include <iostream>
#include <Color.hpp>
#include <Screen.hpp>

using namespace std;

int main() {
  Screen screen;

  screen.Init(200, 200, 3 );

  screen.Draw(100,100,Color::Blue());
  screen.SwitchScreens();

  SDL_Event sdlEvent;
  bool isOpen = true;

  while (isOpen) {
    while (SDL_PollEvent(&sdlEvent)) {
      switch (sdlEvent.type) {
        case SDL_QUIT:isOpen = false;
          break;
      }
    }
  }

  return 0;
}
