//
// Created by stipo on 19. 04. 2020..
//

#ifndef BREAK_OUT_GAME_BLOCK_HPP_
#define BREAK_OUT_GAME_BLOCK_HPP_
#include "Excluder.hpp"
#include "Ball.hpp"
#include "Color.hpp"
#include "Screen.hpp"
#include "BoundaryEdge.hpp"

class Block : public Excluder
{
 public:
	static const int UNBREAKABLE = -1;

	Block() : mHP(1), mColor(Color::Blue())
	{
	}

	void Init(const AARectangle& rectangle, int hp, const Color& color);
	void Draw(Screen& screen);
	void Bounce(Ball& ball, BoundaryEdge edge);

	inline void ReduceHP()
	{
		mHP -= 1;
	}

	inline int GetHP() const
	{
		return mHP;
	}

	inline bool IsDestroyed() const
	{
		return mHP == 0;
	}

	inline Color GetColor() const
	{
		return mColor;
	}

 private:
	Color mColor;
	int mHP;
};

#endif //BREAK_OUT_GAME_BLOCK_HPP_
