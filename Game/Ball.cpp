//
// Created by stipo on 18. 04. 2020..
//

#include "Ball.hpp"
#include "Utils.hpp"
#include "Circle.hpp"
const float Ball::RADIUS = 5.0f;

void Ball::Update(uint32_t dt)
{
	mBBox.MoveBy(mVelocity * MillisecondsToSeconds(dt));
}

void Ball::Draw(Screen& screen)
{
	Circle circle = { mBBox.GetCenter(), GetRadius() };
	screen.Draw(circle, Color::Green());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge)
{
	if (edge.normal == DOWN_DIR)
	{
		mBBox.MoveTo(Vec2D(mBBox.GetTopLeft().GetX(), edge.edge.GetPoint0().GetY() + edge.normal.GetY()));
	}
	else if (edge.normal == UP_DIR)
	{
		mBBox.MoveTo(Vec2D(mBBox.GetTopLeft().GetX(), edge.edge.GetPoint0().GetY() - mBBox.GetHeight()));
	}
	else if (edge.normal == RIGHT_DIR)
	{
		mBBox.MoveTo(Vec2D(edge.edge.GetPoint0().GetX() + edge.normal.GetX(), mBBox.GetTopLeft().GetY()));
	}
	else if (edge.normal == LEFT_DIR)
	{
		mBBox.MoveTo(Vec2D(edge.edge.GetPoint0().GetX() - mBBox.GetWidth(), mBBox.GetTopLeft().GetY()));
	}

	pointOnEdge = edge.edge.ClosestPoint(mBBox.GetCenter(), limitToEdge);

}

void Ball::MoveTo(const Vec2D& point)
{
	mBBox.MoveTo(point - Vec2D(GetRadius(), GetRadius()));
}

void Ball::Bounce(const BoundaryEdge& edge)
{
	Vec2D pointOnEdge;
	MakeFlushWithEdge(edge, pointOnEdge, false);

	mVelocity = mVelocity.Reflect(edge.normal);
}
