//
// Created by stipo on 12. 04. 2020..
//

#include "Screen.hpp"
#include <ScreenBuffer.hpp>
#include <Color.hpp>
#include <iostream>
#include <Vec2D.hpp>
#include <SDL2/SDL.h>

using namespace std;

Screen::~Screen() {
  SDL_DestroyWindow(moPtrWindow);
  SDL_Quit();
}

SDL_Window *Screen::Init(uint32_t width, uint32_t height, uint32_t magnification) {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    cout << "Sh?t happened!" << endl;
    return nullptr;
  }

  mWidth = width;
  mHeight = height;
  moPtrWindow = SDL_CreateWindow("Nerdic",

                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 magnification * mWidth,
                                 magnification * mHeight,
                                 0);

  if (moPtrWindow) {
    mnoPtrWindowSurface = SDL_GetWindowSurface(moPtrWindow);
    SDL_PixelFormat *pixelFormat = mnoPtrWindowSurface->format;
    Color::InitColorFormat(pixelFormat); // OR BOOOOOOOOOOOOOOOOOOOM CRASH

    //  cout << SDL_GetPixelFormatName(pixelFormat->format);

    mClearColor = Color::Black();

    mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
    mBackBuffer.Clear(mClearColor);
  }
  return nullptr;
}

void Screen::SwitchScreens() {
  if (moPtrWindow) {
    ClearScreen();
    SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoPtrWindowSurface, nullptr);

    SDL_UpdateWindowSurface(moPtrWindow);
    mBackBuffer.Clear(mClearColor);
  }
}

void Screen::Draw(int x, int y, const Color &color) {
  if (moPtrWindow) {
    mBackBuffer.SetPixel(color, x, y);
  }
}

void Screen::Draw(const Vec2D &point, const Color &color) {
  if (moPtrWindow) {
    mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
  }
}

void Screen::ClearScreen() {
  if (moPtrWindow) {
    SDL_FillRect(mnoPtrWindowSurface, nullptr, mClearColor.GetPixelColor());
  }
}
