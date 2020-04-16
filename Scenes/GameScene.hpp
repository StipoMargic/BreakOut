//
// Created by stipo on 16. 04. 2020..
//

#ifndef BREAK_OUT_SCENES_GAMESCENE_HPP_
#define BREAK_OUT_SCENES_GAMESCENE_HPP_

#include "Game.hpp"
#include "Scene.hpp"
#include <memory>

class GameScene : public Scene
{
 public:
	GameScene(std::unique_ptr<Game> oPtrGame):mGame(std::move(oPtrGame)){}

	virtual ~GameScene()
	{
	}

	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& theScreen) override;
	virtual std::string GetSceneName() const override;
 private:
	std::unique_ptr<Game> mGame;
};

#endif //BREAK_OUT_SCENES_GAMESCENE_HPP_
