//
// Created by stipo on 15. 04. 2020..
//

#ifndef BREAK_OUT_APP_APP_HPP_
#define BREAK_OUT_APP_APP_HPP_

#include "Screen.hpp"
#include <cstdint>
#include <SDL2/SDL.h>
#include <memory>
#include "InputController.hpp"

class Scene;
class App
{
 public:
	static App& Singleton();
	bool Init(uint32_t width, uint32_t height, uint32_t mag);
	void Run();

	inline uint32_t GetWidth() const
	{
		return mScreen.GetWidth();
	}

	inline uint32_t GetHeight() const
	{
		return mScreen.GetHeight();
	}

	void PushScene(std::unique_ptr<Scene> theScene);
	void PopScene();
	Scene* TopScene();

 private:
	Screen mScreen;
	SDL_Window* mnoPrrWindow;

	std::vector<std::unique_ptr<Scene>> mSceneStack;
	InputController mInputController;
};

#endif //BREAK_OUT_APP_APP_HPP_
