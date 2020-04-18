//
// Created by stipo on 17. 04. 2020..
//

#ifndef BREAK_OUT_GAME_PADDLE_HPP_
#define BREAK_OUT_GAME_PADDLE_HPP_

#include "Excluder.hpp"
#include <cstdint>
#include "Ball.hpp"

class Screen;
enum PaddleDirection
{
	NONE = 0,
	LEFT,
	RIGHT
};
class Paddle : public Excluder
{
 public:
	static const uint32_t PADDLE_WIDTH = 50;
	static const uint32_t PADDLE_HEIGHT = 10;

	void Init(const AARectangle& rectangle, const AARectangle& bouandry);
	void Update(uint32_t dt, Ball& ball);
	void Draw(Screen& screen);
	bool Bounce(Ball& ball);

	inline bool IsMovingLeft() const
	{
		return mDirection == PaddleDirection::LEFT;
	}

	inline bool IsMovingRight() const
	{
		return mDirection == PaddleDirection::RIGHT;
	}

	inline void SetMovementDirection(PaddleDirection direction)
	{
		mDirection = direction;
	}

	inline void StopMovement()
	{
		mDirection = PaddleDirection::NONE;
	}

 private:
	PaddleDirection mDirection;
	AARectangle mBoundary;
	const float VELOCITY = 100; // Pixel per sec

	const float CORNER_OF_PADDLE = 0.2f;
};

#endif //BREAK_OUT_GAME_PADDLE_HPP_
