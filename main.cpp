#include <SDL2/SDL.h>
#include <iostream>
#include <Color.hpp>
#include <cstdint>
#include <ScreenBuffer.hpp>

using namespace std;

int main() {

  if (SDL_Init(SDL_INIT_VIDEO)) {
    cout << "Sh?t happened!" << endl;
    return 1;
  }

  SDL_Window *oPtrWindow = SDL_CreateWindow("Nerdic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200, 0);

  if (oPtrWindow == nullptr) {
    cout << "Sh?t happened again!" << SDL_GetError() << endl;
    return 1;
  }

  SDL_Surface *noPtrWindowSurface = SDL_GetWindowSurface(oPtrWindow);
  SDL_PixelFormat *pixelFormat = noPtrWindowSurface->format;

  cout << SDL_GetPixelFormatName(pixelFormat->format);

  Color::InitColorFormat(pixelFormat); // OR BOOOOOOOOOOOOOOOOOOOM CRASH

  ScreenBuffer screenBuffer;

  screenBuffer.Init(pixelFormat->format, 200, 200);
  screenBuffer.SetPixel(Color::Blue(), 100, 100);
  SDL_BlitSurface(screenBuffer.GetSurface(), nullptr, noPtrWindowSurface, nullptr);

  SDL_UpdateWindowSurface(oPtrWindow);

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

  SDL_DestroyWindow(oPtrWindow);
  SDL_Quit();
  return 0;
}
