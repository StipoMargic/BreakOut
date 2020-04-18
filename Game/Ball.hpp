//
// Created by stipo on 18. 04. 2020..
//

#ifndef BREAK_OUT_GAME_BALL_HPP_
#define BREAK_OUT_GAME_BALL_HPP_

#include "AaRectangle.hpp"
#include "Screen.hpp"
#include "BoundaryEdge.hpp"

class Ball
{
 public:
	Ball() : Ball(Vec2D::Zero, RADIUS)
	{
	}

	Ball(const Vec2D& pos, float radius):mBBox(pos - Vec2D(radius,radius), radius *2.0f,radius * 2.0f), mVelocity(Vec2D::Zero)  {}
	void Update(uint32_t dt);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge);
	void MoveTo(const Vec2D& point);
	void Bounce(const BoundaryEdge& edge);

	inline void Stop()
	{
		mVelocity = Vec2D::Zero;
	}

	inline AARectangle GetBoundingRectangle() const
	{
		return mBBox;
	}

	inline void SetVelocity(const Vec2D& velocity)
	{
		mVelocity = velocity;
	}

	inline Vec2D GetVelocity() const
	{
		return mVelocity;
	}

	inline float GetRadius() const
	{
		return mBBox.GetWidth() / 2;
	}

	inline Vec2D GetPosition() const
	{
		return mBBox.GetCenter();
	}

 private:
	AARectangle mBBox;
	Vec2D mVelocity;

	static const float RADIUS;
};

#endif //BREAK_OUT_GAME_BALL_HPP_
