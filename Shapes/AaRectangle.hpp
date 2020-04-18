//
// Created by stipo on 13. 04. 2020..
//

#ifndef BREAK_OUT_SHAPES_AARECTANGLE_HPP_
#define BREAK_OUT_SHAPES_AARECTANGLE_HPP_
// Access Align Rectangle
#include <Shape.hpp>

class AARectangle : public Shape
{
 public:
	AARectangle() : AARectangle(Vec2D::Zero, Vec2D::Zero)
	{
	}

	AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);
	AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);

	inline void SetTopLeft(const Vec2D& topLeft)
	{
		mPoints[0] = topLeft;
	}

	inline void SetBottomRight(const Vec2D& bottomRight)
	{
		mPoints[1] = bottomRight;
	}

	inline Vec2D GetTopLeft() const
	{
		return mPoints[0];
	}

	inline Vec2D GetBottomRight() const
	{
		return mPoints[1];
	}

	inline float GetHeight() const
	{
		return GetBottomRight().GetY() - GetTopLeft().GetY() + 1;
	}

	inline float GetWidth() const
	{
		return GetBottomRight().GetX() - GetTopLeft().GetX() + 1;
	}

	void MoveTo(const Vec2D& offset);
	bool Intersects(const AARectangle& otherRectangle) const;
	bool ContainsPoint(const Vec2D& point) const;
	virtual Vec2D GetCenter() const override;
	virtual std::vector<Vec2D> GetPoints() const;

	static AARectangle Inset(const AARectangle& rect, Vec2D& insets);
};

#endif //BREAK_OUT_SHAPES_AARECTANGLE_HPP_
