//
// Created by stipo on 2020-04-12.
//

#ifndef BREAK_OUT_SHAPES_LINE2D_HPP_
#define BREAK_OUT_SHAPES_LINE2D_HPP_

#include "Vec2D.hpp"

class Line2D
{
 public:
	Line2D() : Line2D(Vec2D::Zero, Vec2D::Zero)
	{
	}

	Line2D(float x0, float y0, float x1, float y1) : Line2D(Vec2D(x0, y0), Vec2D(x1, y1))
	{
	}

	Line2D(const Vec2D& point0, const Vec2D& point1) : mPoint0(point0), mPoint1(point1)
	{
	}

	inline void SetP0(const Vec2D& point)
	{
		mPoint0 = point;
	}

	inline void SetP1(const Vec2D& point)
	{
		mPoint1 = point;
	}

	inline Vec2D GetPoint0() const
	{
		return mPoint0;
	}

	inline Vec2D GetPoint1() const
	{
		return mPoint1;
	}

	inline float MinDistanceFrom(const Vec2D& p, bool limitToSegment = false) const
	{
		return p.Distance(ClosestPoint(p, limitToSegment));
	}

	bool operator==(Line2D line) const;
	float DistanceFromPoint(const Vec2D& point, bool limitToSegment = false) const;
	Vec2D ClosestPoint(const Vec2D& point, bool limitToSegment = false) const;
	Vec2D Midooint() const;
	float Length() const;
 private:
	Vec2D mPoint0;
	Vec2D mPoint1;
};

#endif //BREAK_OUT_SHAPES_LINE2D_HPP_
