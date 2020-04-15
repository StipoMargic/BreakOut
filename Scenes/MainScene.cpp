//
// Created by stipo on 15. 04. 2020..
//

#include "MainScene.hpp"
#include "Screen.hpp"
#include "Line2D.hpp"

MainScene::MainScene()
{
}

std::string MainScene::GetSceneName() const
{
	return std::string("Name Of Game");
}

void MainScene::Draw(Screen& theScreen)
{
	theScreen.Draw(Line2D(Vec2D(0, 100), Vec2D(200, 100)), Color::Red());
	theScreen.Draw(AARectangle(Vec2D(100, 100), 50, 60), Color::Blue());
	theScreen.Draw(Circle(Vec2D(114, 114), 30), Color::Red());
}

void MainScene::Update(uint32_t dt)
{

}

void MainScene::Init()
{

}

std::unique_ptr<Scene> MainScene::GetScene(eScene scene)
{
	switch (scene)
	{
	case INTRO:
	{

	}
		break;
	case CREDITS:
	{

	}
		break;
	case GAME:
	{

	}
		break;
	default:
	{

	}
		break;
	}

	return nullptr;
}
