//
// Created by stipo on 17. 04. 2020..
//

#include "Excluder.hpp"
#include <cmath>
#include <cassert>
#include "Utils.hpp"

void Excluder::Init(const AARectangle& rectangle, bool reverseNormals)
{
	mAARectangle = rectangle;
	mReverseNormals = reverseNormals;

	SetupEdges();
}

bool Excluder::HasCollided(const AARectangle& rectangle, BoundaryEdge& edge)
{
	if (mAARectangle.Intersects(rectangle))
	{
		float
			yMin = mAARectangle.GetTopLeft().GetY() >= rectangle.GetTopLeft().GetY() ? mAARectangle.GetTopLeft().GetY()
																					 : rectangle.GetTopLeft().GetY();
		float yMax = mAARectangle.GetBottomRight().GetY() <= rectangle.GetBottomRight().GetY()
					 ? mAARectangle.GetBottomRight().GetY() : rectangle.GetBottomRight().GetY();

		float ySize = yMax - yMin;
		float xMin =
			mAARectangle.GetTopLeft().GetX() >= rectangle.GetTopLeft().GetX() ? mAARectangle.GetTopLeft().GetX()
																			  : rectangle.GetTopLeft().GetX();
		float xMax = mAARectangle.GetBottomRight().GetX() <= rectangle.GetBottomRight().GetX()
					 ? mAARectangle.GetBottomRight().GetX() : rectangle.GetBottomRight().GetX();

		float xSize = xMax - xMin;

		if (xSize > ySize)
		{
			if (rectangle.GetCenter().GetY() > mAARectangle.GetCenter().GetY())
			{
				edge = mEdges[BOTTOM_EDGE];
			}
			else
			{
				edge = mEdges[TOP_EDGE];
			}
		}
		else
		{
			if (rectangle.GetCenter().GetX() > mAARectangle.GetCenter().GetX())
			{
				edge = mEdges[RIGHT_EDGE];
			}
			else
			{
				edge = mEdges[LEFT_EDGE];
			}
		}
		return true;
	}
	return false;
}

Vec2D Excluder::GetCollisionOffset(const AARectangle& rectangle)
{
	BoundaryEdge edge;
	Vec2D offset = Vec2D::Zero;
	if (HasCollided(rectangle, edge))
	{
		float
			yMin = mAARectangle.GetTopLeft().GetY() >= rectangle.GetTopLeft().GetY() ? mAARectangle.GetTopLeft().GetY()
																					 : rectangle.GetTopLeft().GetY();
		float yMax = mAARectangle.GetBottomRight().GetY() <= rectangle.GetBottomRight().GetY()
					 ? mAARectangle.GetBottomRight().GetY() : rectangle.GetBottomRight().GetY();

		float ySize = yMax - yMin;
		float xMin =
			mAARectangle.GetTopLeft().GetX() >= rectangle.GetTopLeft().GetX() ? mAARectangle.GetTopLeft().GetX()
																			  : rectangle.GetTopLeft().GetX();
		float xMax = mAARectangle.GetBottomRight().GetX() <= rectangle.GetBottomRight().GetX()
					 ? mAARectangle.GetBottomRight().GetX() : rectangle.GetBottomRight().GetX();

		float xSize = xMax - xMin;

		if (!IsEqual(edge.normal.GetY(), 0))
		{
			offset = (ySize + 1) * edge.normal;
		}
		else
		{
			offset = (xSize + 1) * edge.normal;
		}
	}
	return offset;
}

void Excluder::MoveBy(const Vec2D& offset)
{
	mAARectangle.MoveBy(offset);
	SetupEdges();
}

void Excluder::MoveTo(const Vec2D& point)
{
	mAARectangle.MoveTo(point);
	SetupEdges();
}

const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const
{
	assert(edge != NUM_EDGES);

	return mEdges[edge];
}

void Excluder::SetupEdges()
{
	mEdges[TOP_EDGE].edge =
		{ mAARectangle.GetTopLeft().GetX(), mAARectangle.GetTopLeft().GetY(), mAARectangle.GetBottomRight().GetX(),
		  mAARectangle.GetTopLeft().GetY() };
	mEdges[TOP_EDGE].normal = UP_DIR;

	mEdges[LEFT_EDGE].edge =
		{ mAARectangle.GetTopLeft().GetX(), mAARectangle.GetTopLeft().GetY(), mAARectangle.GetTopLeft().GetX(),
		  mAARectangle.GetBottomRight().GetY() };
	mEdges[LEFT_EDGE].normal = LEFT_DIR;

	mEdges[BOTTOM_EDGE].edge =
		{ mAARectangle.GetTopLeft().GetX(), mAARectangle.GetBottomRight().GetY(), mAARectangle.GetBottomRight().GetX(),
		  mAARectangle.GetBottomRight().GetY() };
	mEdges[BOTTOM_EDGE].normal = DOWN_DIR;

	mEdges[RIGHT_EDGE].edge =
		{ mAARectangle.GetBottomRight().GetX(), mAARectangle.GetTopLeft().GetY(), mAARectangle.GetBottomRight().GetX(),
		  mAARectangle.GetBottomRight().GetY() };
	mEdges[RIGHT_EDGE].normal = RIGHT_DIR;

	if (mReverseNormals)
	{
		for (auto& edge : mEdges)
		{
			edge.normal = -edge.normal;
		}
	}
}
