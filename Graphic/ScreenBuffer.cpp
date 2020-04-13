//
// Created by stipo on 12. 04. 2020..
//

#include <SDL_surface.h>
#include <cassert>
#include "ScreenBuffer.hpp"

ScreenBuffer::ScreenBuffer(const ScreenBuffer& screenBuffer)
{
  mSurface = SDL_CreateRGBSurfaceWithFormat(0,
                                            screenBuffer.mSurface->w,
                                            screenBuffer.mSurface->h,
                                            0,
                                            screenBuffer.mSurface->format->format);

  SDL_BlitSurface(screenBuffer.mSurface, nullptr, mSurface, nullptr);
}

ScreenBuffer::~ScreenBuffer()
{
  assert(mSurface);
  if (mSurface)
  {
    SDL_FreeSurface(mSurface);
  }
}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& screenBuffer)
{
  if (this == &screenBuffer)
  {
    return *this;
  }

  if (mSurface != nullptr)
  {
    SDL_FreeSurface(mSurface);
  }

  if (screenBuffer.mSurface != nullptr)
  {
    SDL_CreateRGBSurfaceWithFormat(0,
                                   screenBuffer.mSurface->w,
                                   screenBuffer.mSurface->h,
                                   0,
                                   screenBuffer.mSurface->format->format);
    SDL_BlitSurface(screenBuffer.mSurface, nullptr, mSurface, nullptr);
  }

  return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t height)
{
  mSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
  Clear();
}

void ScreenBuffer::Clear(const Color& c)
{
  SDL_FillRect(mSurface, nullptr, c.GetPixelColor());
}

void ScreenBuffer::SetPixel(const Color& color, int x, int y)
{
  SDL_LockSurface(mSurface);
  if (mSurface && (y < mSurface->h && y >= 0 && x < mSurface->w && x >= 0))
  {
    uint32_t* pixels = (uint32_t*)mSurface->pixels;
    uint32_t index = GetIndex(y, x);

    pixels[ index ] = color.GetPixelColor();
  }
  SDL_UnlockSurface(mSurface);
}

uint32_t ScreenBuffer::GetIndex(int row, int column) const
{
  assert(mSurface);
  if (mSurface)
  {
    return row * mSurface->w + column;
  }
}