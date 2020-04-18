//
// Created by stipo on 17. 04. 2020..
//

#ifndef BREAK_OUT_GAME_BREAKOUT_HPP_
#define BREAK_OUT_GAME_BREAKOUT_HPP_

#include "Game.hpp"
#include "Paddle.hpp"

class Breakout: public Game
{
 public:
	void Init(GameController& gameController) override ;
	void Update(uint32_t dt) override ;
	void Draw(Screen& screen) override ;
	std::string GetName() override {return "Nerdic";}

 private:
	Paddle mPaddle;
	void ResetGame();
};

#endif //BREAK_OUT_GAME_BREAKOUT_HPP_
