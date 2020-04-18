//
// Created by stipo on 17. 04. 2020..
//

#ifndef BREAK_OUT_GAME_BOUNDARYEDGE_HPP_
#define BREAK_OUT_GAME_BOUNDARYEDGE_HPP_

#include "Vec2D.hpp"
#include "Line2D.hpp"

static const Vec2D UP_DIR = {0,-1};
static const Vec2D DOWN_DIR = {0,1};
static const Vec2D LEFT_DIR = {-1,0};
static const Vec2D RIGHT_DIR = {1,0};

enum EdgeType {
	BOTTOM_EDGE = 0,
	TOP_EDGE,
	LEFT_EDGE,
	RIGHT_EDGE,
	NUM_EDGES
};

struct BoundaryEdge
{
	Vec2D normal;
	Line2D edge;
};

#endif //BREAK_OUT_GAME_BOUNDRYEDGE_HPP_
