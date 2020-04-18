//
// Created by stipo on 17. 04. 2020..
//

#include "Paddle.hpp"
#include "Screen.hpp"
#include "Utils.hpp"
#include "BoundaryEdge.hpp"

void Paddle::Init(const AARectangle& rectangle)
{
	Excluder::Init(rectangle);
		mDirection = PaddleDirection::NONE;
}

void Paddle::Update(uint32_t dt)
{
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

	}

}

void Paddle::Draw(Screen& screen)
{
	screen.Draw(GetRectangle(), Color::White());
}
