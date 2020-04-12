//
// Created by stipo on 12. 04. 2020..
//

#ifndef BREAK_OUT_UTILS_SCREEN_HPP_
#define BREAK_OUT_UTILS_SCREEN_HPP_

#include <cstdint>
#include <ScreenBuffer.hpp>
#include <Color.hpp>

class SDL_Window;

class Vec2D;
class Line2D;
class SDL_Surface;

class Screen {
 public:
  Screen() : mWidth(0), mHeight(0), moPtrWindow(nullptr), mnoPtrWindowSurface(nullptr) {}

  ~Screen();
  SDL_Window *Init(uint32_t width, uint32_t height, uint32_t magnification);
  void SwitchScreens();

  inline void SetClearColor(const Color &color) { mClearColor = color.GetPixelColor(); }

  inline Color GetClearColor() { return mClearColor; }

  inline uint32_t GetHeight() { return mHeight; }

  inline uint32_t GetWidth() { return mWidth; }

  // Draw Methods
  void Draw(int x, int y, const Color &color); // Pass cord
  void Draw(const Vec2D &point, const Color &color); // Pass Vector
  void Draw(const Line2D &line, const Color &color); // Draw 2D Line

 private:
  Screen(const Screen &screen); // Only I can copy
  Screen &operator=(const Screen &screen);
  void ClearScreen();
  uint32_t mHeight;
  uint32_t mWidth;
  Color mClearColor;
  ScreenBuffer mBackBuffer;
  SDL_Window *moPtrWindow;
  SDL_Surface *mnoPtrWindowSurface;
};

#endif //BREAK_OUT_UTILS_SCREEN_HPP_
