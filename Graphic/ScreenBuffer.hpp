//
// Created by stipo on 12. 04. 2020..
//

#ifndef BREAK_OUT_UTILS_SCREENBUFFER_HPP_
#define BREAK_OUT_UTILS_SCREENBUFFER_HPP_

#include "Color.hpp"
#include <cstdint>

class SDL_Surface;

class ScreenBuffer {
 public:
  ScreenBuffer() : mSurface(nullptr) {}
  ScreenBuffer(const ScreenBuffer &screenBuffer);
  ~ScreenBuffer();
  ScreenBuffer &operator=(const ScreenBuffer &screenBuffer);
  void Init(uint32_t format, uint32_t width, uint32_t height);

  inline SDL_Surface *GetSurface() { return mSurface; };

  void Clear(const Color &c = Color::Black());
  void SetPixel(const Color &color, int x, int y);
 private:
  SDL_Surface *mSurface;
  uint32_t GetIndex(int row, int column);
};

#endif //BREAK_OUT_UTILS_SCREENBUFFER_HPP_