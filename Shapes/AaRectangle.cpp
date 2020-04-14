//
// Created by stipo on 13. 04. 2020..
//

#include "AaRectangle.hpp"

AARectangle::AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height)
{
	mPoints.push_back(topLeft);
	mPoints.push_back(Vec2D(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1));
}

AARectangle::AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight)
{
	mPoints.push_back(topLeft);
	mPoints.push_back(bottomRight);
}

void AARectangle::MoveTo(const Vec2D& offset)
{
	SetTopLeft(offset);
	SetBottomRight(Vec2D(GetTopLeft().GetX() + GetWidth() - 1, GetTopLeft().GetY() + GetHeight() - 1));
}

Vec2D AARectangle::GetCenter() const
{
	return Vec2D(GetTopLeft().GetX() + GetWidth() / 2.0f, GetTopLeft().GetY() + GetWidth() / 2.0f);
}

bool AARectangle::ContainsPoint(const Vec2D& point) const
{
	bool withinX = point.GetX() >= GetTopLeft().GetX() && point.GetX() <= GetBottomRight().GetX();
	bool withinY = point.GetY() >= GetTopLeft().GetY() && point.GetY() <= GetBottomRight().GetY();

	return withinX && withinY;
}

std::vector<Vec2D> AARectangle::GetPoints() const
{
	std::vector<Vec2D> points;

	// Insert all 4 points clockwise
	points.push_back(mPoints[0]);
	points.push_back(Vec2D(mPoints[1].GetX(), mPoints[0].GetY()));
	points.push_back(mPoints[1]);
	points.push_back(Vec2D(mPoints[0].GetX(), mPoints[1].GetY()));

	return points;
}

bool AARectangle::Intersects(const AARectangle& otherRectangle) const
{
	return !(otherRectangle.GetBottomRight().GetX() < GetTopLeft().GetX() ||
		otherRectangle.GetTopLeft().GetX() > GetBottomRight().GetX() ||
		otherRectangle.GetBottomRight().GetY() < GetTopLeft().GetY() ||
		otherRectangle.GetTopLeft().GetY() > GetBottomRight().GetY());
}
AARectangle AARectangle::Inset(const AARectangle& rect, Vec2D& insets)
{
	return AARectangle(rect.GetTopLeft() + insets,
		rect.GetWidth() - 2 * insets.GetX(),
		rect.GetHeight() - 2 * insets.GetY());
}

