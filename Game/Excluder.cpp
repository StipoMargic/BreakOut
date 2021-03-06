//
// Created by stipo on 17. 04. 2020..
//

#include "Excluder.hpp"
#include <cmath>
#include <cassert>
#include "Utils.hpp"
void Excluder::Init(const AARectangle& rect, bool reverseNormals)
{
	mAARectangle = rect;
	mReverseNormals = reverseNormals;
	SetupEdges();
}

bool Excluder::HasCollided(const AARectangle& rect, BoundaryEdge& edge) const
{
	if(mAARectangle.Intersects(rect))
	{
		float yMin = mAARectangle.GetTopLeft().GetY() >= (rect.GetTopLeft().GetY()) ? mAARectangle.GetTopLeft().GetY() : rect.GetTopLeft().GetY();
		float yMax = mAARectangle.GetBottomRight().GetY() <= rect.GetBottomRight().GetY() ? mAARectangle.GetBottomRight().GetY() : rect.GetBottomRight().GetY();

		float ySize = yMax - yMin;

		float xMin = mAARectangle.GetTopLeft().GetX() >= rect.GetTopLeft().GetX() ? mAARectangle.GetTopLeft().GetX() : rect.GetTopLeft().GetX();
		float xMax = mAARectangle.GetBottomRight().GetX() <= rect.GetBottomRight().GetX() ? mAARectangle.GetBottomRight().GetX() : rect.GetBottomRight().GetX();

		float xSize = xMax - xMin;

		if(xSize > ySize)
		{
			if(rect.GetCenter().GetY() > mAARectangle.GetCenter().GetY())
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
			if(rect.GetCenter().GetX() < mAARectangle.GetCenter().GetX())
			{
				edge = mEdges[LEFT_EDGE];
			}
			else
			{
				edge = mEdges[RIGHT_EDGE];
			}
		}

		return true;
	}

	return false;
}

Vec2D Excluder::GetCollisionOffset(const AARectangle& rect) const
{
	BoundaryEdge edge;
	Vec2D offset = Vec2D::Zero;

	if(HasCollided(rect, edge))
	{
		float yMin = mAARectangle.GetTopLeft().GetY() >= (rect.GetTopLeft().GetY()) ? mAARectangle.GetTopLeft().GetY() : rect.GetTopLeft().GetY();
		float yMax = mAARectangle.GetBottomRight().GetY() <= rect.GetBottomRight().GetY() ? mAARectangle.GetBottomRight().GetY() : rect.GetBottomRight().GetY();

		float ySize = yMax - yMin;

		float xMin = mAARectangle.GetTopLeft().GetX() >= rect.GetTopLeft().GetX() ? mAARectangle.GetTopLeft().GetX() : rect.GetTopLeft().GetX();
		float xMax = mAARectangle.GetBottomRight().GetX() <= rect.GetBottomRight().GetX() ? mAARectangle.GetBottomRight().GetX() : rect.GetBottomRight().GetX();

		float xSize = xMax - xMin;

		if(!IsEqual(edge.normal.GetY(), 0))
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

void Excluder::MoveBy(const Vec2D& delta)
{
	mAARectangle.MoveBy(delta);
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