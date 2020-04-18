//
// Created by stipo on 17. 04. 2020..
//

#include <cassert>
#include "Paddle.hpp"
#include "Screen.hpp"
#include "Utils.hpp"
#include "BoundaryEdge.hpp"

void Paddle::Init(const AARectangle& rectangle, const AARectangle& boundary)
{
	Excluder::Init(rectangle);
	mBoundary = boundary;
	mDirection = PaddleDirection::NONE;
}

void Paddle::Update(uint32_t dt, Ball& ball)
{
	if (GetRectangle().ContainsPoint(ball.GetPosition())){
		Vec2D pointOnEdge;
		ball.MakeFlushWithEdge(GetEdge(BOTTOM_EDGE), pointOnEdge, true);
	}

	if (mDirection != PaddleDirection::NONE)
	{
		Vec2D dir;
		if (mDirection == PaddleDirection::RIGHT)
		{
			dir = RIGHT_DIR;
		}
		else
		{
			dir = LEFT_DIR;
		}
		Vec2D dx = dir * VELOCITY * MillisecondsToSeconds(dt);

		MoveBy(dx);

		const AARectangle& aaRect = GetRectangle();

		if (IsGreaterThanOrEqual(mBoundary.GetTopLeft().GetX(), aaRect.GetTopLeft().GetX()))
		{
			MoveTo(Vec2D(mBoundary.GetTopLeft().GetX(), aaRect.GetTopLeft().GetY()));
		}
		else if (IsGreaterThanOrEqual(aaRect.GetBottomRight().GetX(), mBoundary.GetBottomRight().GetX()))
		{
			MoveTo(Vec2D(mBoundary.GetBottomRight().GetX() - aaRect.GetWidth(), aaRect.GetTopLeft().GetY()));
		}

	}

}

void Paddle::Draw(Screen& screen)
{
	screen.Draw(GetRectangle(), Color::White());
}

bool Paddle::Bounce(Ball& ball)
{
	BoundaryEdge edge;
	if (HasCollided(ball.GetBoundingRectangle(), edge))
	{
		Vec2D pointOnEdge;
		ball.MakeFlushWithEdge(edge, pointOnEdge, true);

		if (edge.edge == GetEdge(TOP_EDGE).edge)
		{
			float edgeLength = edge.edge.Length();
			assert(!IsEqual(edgeLength, 0));
			float tx = (pointOnEdge.GetX() - edge.edge.GetPoint0().GetX()) / edgeLength;

			if ((tx <= CORNER_OF_PADDLE && ball.GetVelocity().GetX() > 0) ||
				(tx >= 1.0f - CORNER_OF_PADDLE && ball.GetVelocity().GetX() < 0))
			{
				ball.SetVelocity(-ball.GetVelocity());
				return true;
			}
		}
		ball.SetVelocity(ball.GetVelocity().Reflect(edge.normal));
		return true;
	}
	return false;
}
