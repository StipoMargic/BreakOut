//
// Created by stipo on 15. 04. 2020..
//
#include <iostream>

#include "App.hpp"
#include "Circle.hpp"
#include "AaRectangle.hpp"
#include "Color.hpp"
#include "Line2D.hpp"
#include <SDL2/SDL.h>
#include <cassert>
#include "MainScene.hpp"
#include <memory>

App& App::Singleton()
{
	static App theApp;

	return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t magnification)
{
	mnoPrrWindow = mScreen.Init(width, height, magnification);
	std::unique_ptr<MainScene> mainScene = std::make_unique<MainScene>();

	PushScene(std::move(mainScene));
	return mnoPrrWindow != nullptr;
}

void App::Run()
{
	assert(mnoPrrWindow);
	if (mnoPrrWindow)
	{
		bool isOpen = true;

		uint32_t lastTick = SDL_GetTicks(); // MS since init
		uint32_t currentTick = lastTick;

		uint32_t dt = 10; // Delta time update game every x sec
		uint32_t accumulator = 0; // how many ticks happend

		mInputController.Init([&isOpen](uint32_t dt, InputState state)
		{
		  isOpen = false;
		});

		while (isOpen)
		{
			currentTick = SDL_GetTicks();
			uint32_t frameTime = currentTick - lastTick;

			if (frameTime > 300)
			{
				frameTime = 300; // Cap to 300
			}
			lastTick = currentTick;
			accumulator += frameTime;

			mInputController.Update(dt);

			Scene* topScene = App::TopScene();
			while (accumulator >= dt)
			{
				topScene->Update(dt);
				accumulator -= dt;
			}

			topScene->Draw(mScreen);
			mScreen.SwitchScreens();
		}
	}
}

void App::PushScene(std::unique_ptr<Scene> theScene)
{
	theScene->Init();
	mInputController.SetGameController(theScene->GetGameController());
	mSceneStack.emplace_back(std::move(theScene));
	SDL_SetWindowTitle(mnoPrrWindow, TopScene()->GetSceneName().c_str());
}

void App::PopScene()
{
	if (mSceneStack.size() > 1)
	{
		mSceneStack.pop_back();
		mInputController.SetGameController(TopScene()->GetGameController());
	}

	SDL_SetWindowTitle(mnoPrrWindow, TopScene()->GetSceneName().c_str());
}

Scene* App::TopScene()
{
	if (mSceneStack.empty()) return nullptr;

	return mSceneStack.back().get();
}
