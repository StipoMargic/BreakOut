//
// Created by stipo on 19. 04. 2020..
//

#include "Block.hpp"

void Block::Init(const AARectangle& rectangle, int hp, const Color& color)
{
	Excluder::Init(rectangle);
	mHP = hp;
	mColor = color;
}

void Block::Draw(Screen& screen)
{
	screen.Draw(GetRectangle(), mColor);
}

void Block::Bounce(Ball& ball, BoundaryEdge edge)
{
	ball.Bounce(edge);
}
