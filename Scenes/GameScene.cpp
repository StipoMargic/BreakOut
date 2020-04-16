//
// Created by stipo on 16. 04. 2020..
//

#include "GameScene.hpp"

void GameScene::Init()
{
	mGame->Init(mGameController);
}

void GameScene::Update(uint32_t dt)
{
	mGame->Update(dt);
}

void GameScene::Draw(Screen& theScreen)
{
	mGame->Draw(theScreen);
}

std::string GameScene::GetSceneName() const
{
	return std::string("Ycene Name");
}
