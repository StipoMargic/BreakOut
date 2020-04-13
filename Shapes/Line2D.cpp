//
// Created by stipo on 2020-04-12.
//

#include "Line2D.hpp"
#include "Utils.hpp"
#include <cmath>

bool Line2D::operator==(Line2D line) const
{
  return line.GetPoint0() == mPoint0 && line.GetPoint1() == mPoint1;
}

float Line2D::DistanceFromPoint(const Vec2D& point, bool limitToSegment) const
{
  return mPoint1.Distance(ClosestPoint(point, limitToSegment));
}

Vec2D Line2D::ClosestPoint(const Vec2D& point, bool limitToSegment) const
{
  Vec2D p0ToPoint = point - mPoint0;
  Vec2D p0ToP1 = mPoint1 - mPoint0;
  float l2 = p0ToP1.Mag2();
  float dot = p0ToPoint.Dot(p0ToP1);
  float t = dot / l2;

  if (limitToSegment)
  {
    t = std::fmax(0, std::fmin(1.0f, t));
  }

  return mPoint0 + p0ToP1 * t;
}

Vec2D Line2D::Midooint() const
{
  return Vec2D((mPoint0.GetX() + mPoint1.GetX()) / 2.0f, (mPoint0.GetY() + mPoint1.GetY()) / 2.0f);
}

float Line2D::Length() const
{
  return mPoint0.Distance(mPoint1);
}
