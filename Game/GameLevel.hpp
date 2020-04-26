//
// Created by stipo on 19. 04. 2020..
//

#ifndef BREAK_OUT_GAME_GAMELEVEL_HPP_
#define BREAK_OUT_GAME_GAMELEVEL_HPP_

#include "Ball.hpp"
#include "Block.hpp"
#include "Screen.hpp"
#include <vector>

class GameLevel
{
 public:
	GameLevel()
	{
	}

	void Init(const AARectangle& boundary);
	void Load(const std::vector<Block>& blocks);

	bool IsLevelComplete() const;
	void Update(uint32_t dt, Ball& ball);
	void Draw(Screen& screen);
 private:
	void DefaultLevel(const AARectangle& boundary);
	std::vector<Block> mBlocks;
};

#endif //BREAK_OUT_GAME_GAMELEVEL_HPP_
