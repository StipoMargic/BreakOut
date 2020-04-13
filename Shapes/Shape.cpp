//
// Created by stipo on 13. 04. 2020..
//

#include "Shape.hpp"

void Shape::MoveBy(const Vec2D& offset)
{
	for (Vec2D& point : mPoints)
	{
		point += offset;
	}
}
