//
// Created by stipo on 12. 04. 2020..
//

#include "Screen.hpp"
#include <Line2D.hpp>
#include <Color.hpp>
#include <iostream>
#include <Vec2D.hpp>
#include <SDL2/SDL.h>
#include <cassert>
#include "Utils.hpp"
#include "Circle.hpp"
#include <AaRectangle.hpp>
#include <algorithm>

using namespace std;

Screen::~Screen()
{
	SDL_DestroyWindow(moPtrWindow);
	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t width, uint32_t height, uint32_t magnification)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
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

	if (moPtrWindow)
	{
		mnoPtrWindowSurface = SDL_GetWindowSurface(moPtrWindow);
		SDL_PixelFormat* pixelFormat = mnoPtrWindowSurface->format;
		Color::InitColorFormat(pixelFormat); // OR BOOOOOOOOOOOOOOOOOOOM CRASH

		//  cout << SDL_GetPixelFormatName(pixelFormat->format);

		mClearColor = Color::Black();

		mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
		mBackBuffer.Clear(mClearColor);
	}
	return nullptr;
}

void Screen::SwitchScreens()
{
	assert(moPtrWindow);

	if (moPtrWindow)
	{
		ClearScreen();
		SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoPtrWindowSurface, nullptr);

		SDL_UpdateWindowSurface(moPtrWindow);
		mBackBuffer.Clear(mClearColor);
	}
}

void Screen::Draw(int x, int y, const Color& color)
{
	assert(moPtrWindow);

	if (moPtrWindow)
	{
		mBackBuffer.SetPixel(color, x, y);
	}
}

void Screen::Draw(const Vec2D& point, const Color& color)
{
	assert(moPtrWindow);

	if (moPtrWindow)
	{
		mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
	}
}

void Screen::ClearScreen()
{
	assert(moPtrWindow);

	if (moPtrWindow)
	{
		SDL_FillRect(mnoPtrWindowSurface, nullptr, mClearColor.GetPixelColor());
	}
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm Bresenham's line algorithm
void Screen::Draw(const Line2D& line, const Color& color)
{
	assert(moPtrWindow);
	if (moPtrWindow)
	{
		int dx, dy;
		int x0 = roundf(line.GetPoint0().GetX());
		int y0 = roundf(line.GetPoint0().GetY());
		int x1 = roundf(line.GetPoint1().GetX());
		int y1 = roundf(line.GetPoint1().GetY());

		dx = x1 - x0;
		dy = y1 - y0;

		signed const char ix((dx > 0) - (dx < 0)); // 1 or -1
		signed const char iy((dy > 0) - (dy < 0)); // 1 or -1

		dx = abs(dx) * 2;
		dy = abs(dy) * 2;

		Draw(x0, y0, color);

		if (dx >= dy)
		{
			// increase x
			int d = dy - dx / 2;

			while (x0 != x1)
			{
				if (d >= 0)
				{
					d -= dx;
					y0 += iy;
				}

				d += dy;
				x0 += ix;

				Draw(x0, y0, color);
			}
		}
		else
		{
			// increase y
			int d = dx - dy / 2;

			while (y0 != y1)
			{
				if (d >= 0)
				{
					d -= dy;
					x0 += ix;
				}

				d += dx;
				y0 += iy;

				Draw(x0, y0, color);
			}
		}
	}
}

void Screen::Draw(const AARectangle& rectangle, const Color& color, bool fill)
{
	if (fill)
	{
		ColorFill(rectangle.GetPoints(), color);
	}
	std::vector<Vec2D> points = rectangle.GetPoints();
	Line2D p0top1(points[0], points[1]);
	Line2D p1top2(points[1], points[2]);
	Line2D p2top3(points[2], points[3]);
	Line2D p3top0(points[3], points[0]);

	Draw(p0top1, color);
	Draw(p1top2, color);
	Draw(p2top3, color);
	Draw(p3top0, color);
}

void Screen::Draw(const Circle& circle, const Color& color, bool fill)
{

	static unsigned int NUMBER_OF_LINE_SEGMENT = 50;
	std::vector<Vec2D> circlePoints;
	std::vector<Line2D> lines;
	float angle = TWO_PI / float(NUMBER_OF_LINE_SEGMENT);

	Vec2D p0 = Vec2D(circle.GetCenter().GetX() + circle.GetRadius(), circle.GetCenter().GetY());
	Vec2D p1 = p0;

	Line2D nextLineToDraw;

	for (int i = 0; i < NUMBER_OF_LINE_SEGMENT; ++i)
	{
		p1.Rotate(angle, circle.GetCenter());
		nextLineToDraw.SetP1(p1);
		nextLineToDraw.SetP0(p0);

		lines.push_back(nextLineToDraw);
		p0 = p1;
		circlePoints.push_back(p0);
	}

	if (fill)
	{
		ColorFill(circlePoints, color);
	}
}

// PolyFill Algorithm
void Screen::ColorFill(const vector<Vec2D>& points, const Color& color)
{
	if (points.size() > 0)
	{
		float top = points[0].GetY();
		float bottom = points[0].GetY();
		float right = points[0].GetX();
		float left = points[0].GetX();

		for (size_t i = 1; i < points.size(); ++i)
		{
			if (points[i].GetY() < top)
			{
				top = points[i].GetY();
			}

			if (points[i].GetY() > bottom)
			{
				bottom = points[i].GetY();
			}

			if (points[i].GetX() < left)
			{
				left = points[i].GetX();
			}

			if (points[i].GetX() > right)
			{
				right = points[i].GetX();
			}
		}

		for (int pixelY = top; pixelY < bottom; ++pixelY)
		{
			std::vector<float> nodeXVec;

			size_t j = points.size() - 1;

			for (size_t i = 0; i < points.size(); ++i)
			{
				float pointiY = points[i].GetY();
				float pointjY = points[j].GetY();

				if ((pointiY <= (float)pixelY && pointjY > (float)pixelY)
					|| (pointjY <= (float)pixelY && pointiY > (float)pixelY))
				{
					float denom = pointjY - pointiY;
					if (IsEqual(denom, 0))
					{
						continue;
					}

					float x = points[i].GetX() + (pixelY - pointiY) / (denom) * (points[j].GetX() - points[i].GetX());
					nodeXVec.push_back(x);
				}

				j = i;
			}

			std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

			for (size_t k = 0; k < nodeXVec.size(); k += 2)
			{
				if (nodeXVec[k] > right)
				{
					break;
				}

				if (nodeXVec[k + 1] > left)
				{
					if (nodeXVec[k] < left)
					{
						nodeXVec[k] = left;
					}
					if (nodeXVec[k + 1] > right)
					{
						nodeXVec[k + 1] = right;
					}
					for (int pixelX = nodeXVec[k]; pixelX < nodeXVec[k + 1]; ++pixelX)
					{
						Draw(pixelX, pixelY, color);
					}
				}
			}
		}
	}
}
