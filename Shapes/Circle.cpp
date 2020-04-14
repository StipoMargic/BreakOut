//
// Created by stipo on 14. 04. 2020..
//

#include "Circle.hpp"
#include "Utils.hpp"
bool Circle::Contains(const Vec2D& point) const
{
	return IsLessThanOrEqual(GetCenter().Distance(point), mRadius);
}

bool Circle::Intersects(const Circle& otherCircle) const
{
	return GetCenter().Distance(otherCircle.GetCenter()) < (mRadius + otherCircle.GetRadius());
}
