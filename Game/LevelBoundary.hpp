//
// Created by stipo on 18. 04. 2020..
//

#ifndef BREAK_OUT_GAME_LEVELBOUNDARY_HPP_
#define BREAK_OUT_GAME_LEVELBOUNDARY_HPP_
#include "Excluder.hpp"
#include "Ball.hpp"
#include "Line2D.hpp"

class LevelBoundary
{
 public:
	LevelBoundary()
	{
	}

	LevelBoundary(const AARectangle& boundary);
	bool HasCollied(const Ball& ball, BoundaryEdge& edge);

	inline const AARectangle& GetAARectangle() const
	{
		return mIncluder.GetRectangle();
	}

 private:
	Excluder mIncluder;
	bool HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const;
};

#endif //BREAK_OUT_GAME_LEVELBOUNDARY_HPP_
