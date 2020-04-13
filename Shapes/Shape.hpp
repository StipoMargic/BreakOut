//
// Created by stipo on 13. 04. 2020..
//

#ifndef BREAK_OUT_SHAPES_SHAPE_HPP_
#define BREAK_OUT_SHAPES_SHAPE_HPP_

#include <Vec2D.hpp>
#include <vector>

class Shape
{
 public:
		virtual Vec2D GetCenter() const = 0;

		virtual ~Shape()
		{ }

		inline virtual std::vector<Vec2D> const GetPoints()
		{ return mPoints; }

		void MoveBy(const Vec2D& offset);

 protected:
		std::vector<Vec2D> mPoints;
};

#endif //BREAK_OUT_SHAPES_SHAPE_HPP_
