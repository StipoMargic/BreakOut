//
// Created by stipo on 17. 04. 2020..
//

#ifndef BREAK_OUT_GAME_EXCLUDER_HPP_
#define BREAK_OUT_GAME_EXCLUDER_HPP_

#include "AaRectangle.hpp"
#include "BoundaryEdge.hpp"

class Excluder
{
 public:
	virtual ~Excluder()
	{
	}

	void Init(const AARectangle& rectangle, bool reverseNormals = false);
	bool  HasCollided(const AARectangle& rectangle, BoundaryEdge& edge) const ;
	Vec2D GetCollisionOffset(const AARectangle& rectangle) const ;
	void MoveBy(const Vec2D& offset);
	void MoveTo(const Vec2D& point);

	const BoundaryEdge& GetEdge(EdgeType edge) const;

	inline AARectangle& GetRectangle()
	{
		return mAARectangle;
	}

 private:
	void SetupEdges();
	AARectangle mAARectangle;
	BoundaryEdge mEdges[NUM_EDGES];
	bool mReverseNormals;
};

#endif //BREAK_OUT_GAME_EXCLUDER_HPP_
