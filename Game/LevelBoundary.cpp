//
// Created by stipo on 18. 04. 2020..
//

#include "LevelBoundary.hpp"
#include "Ball.hpp"

bool LevelBoundary::HasCollied(const Ball& ball, BoundaryEdge& edge)
{
	for (int i = 0; i < NUM_EDGES; ++i)
	{
		BoundaryEdge collisionEdge = mIncluder.GetEdge(static_cast<EdgeType>(i));
		if (HasCollidedWithEdge(ball, collisionEdge))
		{
			edge = collisionEdge;
			return true;
		}
	}
	return false;

}

bool LevelBoundary::HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const
{
	return edge.edge.MinDistanceFrom(ball.GetPosition()) < ball.GetRadius();
}

LevelBoundary::LevelBoundary(const AARectangle& boundary)
{
	mIncluder.Init(boundary, true);
}
