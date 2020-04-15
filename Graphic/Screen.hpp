//
// Created by stipo on 12. 04. 2020..
//

#ifndef BREAK_OUT_UTILS_SCREEN_HPP_
#define BREAK_OUT_UTILS_SCREEN_HPP_

#include <cstdint>
#include "ScreenBuffer.hpp"
#include "Color.hpp"
#include <AaRectangle.hpp>
#include <Circle.hpp>
#include <vector>

class Vec2D;
class Line2D;
struct SDL_Window;
struct SDL_Surface;
class Screen
{
 public:
	Screen() : mWidth(0), mHeight(0), moPtrWindow(nullptr), mnoPtrWindowSurface(nullptr)
	{
	}

	~Screen();
	SDL_Window* Init(uint32_t width, uint32_t height, uint32_t magnification);
	void SwitchScreens();

	inline void SetClearColor(const Color& color)
	{
		mClearColor = color.GetPixelColor();
	}

	inline Color GetClearColor()
	{
		return mClearColor;
	}

	inline uint32_t GetHeight() const
	{
		return mHeight;
	}

	inline uint32_t GetWidth() const
	{
		return mWidth;
	}

	// Draw Methods
	void Draw(int x, int y, const Color& color); // Pass cord
	void Draw(const Vec2D& point, const Color& color); // Pass Vector
	void Draw(const Line2D& line, const Color& color); // Draw 2D Line
	void Draw(const AARectangle& rectangle, const Color& color, bool fill = true); // Draw Rectangle
	void Draw(const Circle& circle, const Color& color, bool fill = true); // Draw Circle

 private:
	Screen(const Screen& screen); // Only I can copy
	Screen& operator=(const Screen& screen);
	void ClearScreen();
	void ColorFill(const std::vector<Vec2D>& points, const Color& color);
	uint32_t mHeight;
	uint32_t mWidth;
	Color mClearColor;
	ScreenBuffer mBackBuffer;
	SDL_Window* moPtrWindow;
	SDL_Surface* mnoPtrWindowSurface;
};

#endif //BREAK_OUT_UTILS_SCREEN_HPP_
