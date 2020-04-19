//
// Created by stipo on 17. 04. 2020..
//

#ifndef BREAK_OUT_GAME_BREAKOUT_HPP_
#define BREAK_OUT_GAME_BREAKOUT_HPP_

#include "Game.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "LevelBoundary.hpp"
#include "GameLevel.hpp"

class Breakout: public Game
{
 public:
	void Init(GameController& gameController) override ;
	void Update(uint32_t dt) override ;
	void Draw(Screen& screen) override ;
	const std::string& GetName() override;

 private:
	GameLevel mLevel;
	Paddle mPaddle;
	Ball mBall;
	LevelBoundary mLevelBoundary;
	void ResetGame();

	const Vec2D INITIAL_VELOCITY = {100,- 100};
};

#endif //BREAK_OUT_GAME_BREAKOUT_HPP_
