//
// Created by stipo on 14. 04. 2020..
//

#ifndef BREAK_OUT_SHAPES_CIRCLE_HPP_
#define BREAK_OUT_SHAPES_CIRCLE_HPP_

#include "Shape.hpp"
#include "Vec2D.hpp"
class Circle : public Shape
{
 public:
	Circle() : Circle(Vec2D::Zero, 0)
	{
	}
	Circle(const Vec2D& center, float radius) : mRadius(radius)
	{
		mPoints.push_back(center);
	}

	[[nodiscard]] inline Vec2D GetCenter() const override
	{
		return mPoints[0];
	}
	[[nodiscard]] inline float GetRadius() const
	{
		return mRadius;
	}
	inline void SetRadius(float radius)
	{
		mRadius = radius;
	}

	inline void MoveTo(const Vec2D& position)
	{
		mPoints[0] = position;
	}

	[[nodiscard]] bool Intersects(const Circle& otherCircle) const;
	[[nodiscard]] bool Contains(const Vec2D& point) const;
 private:
	float mRadius;
};

#endif //BREAK_OUT_SHAPES_CIRCLE_HPP_
