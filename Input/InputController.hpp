//
// Created by stipo on 16. 04. 2020..
//

#ifndef BREAK_OUT_INPUT_INPUTCONTROLLER_HPP_
#define BREAK_OUT_INPUT_INPUTCONTROLLER_HPP_
#include "InputAction.hpp"
class GameController;

class InputController
{
 public:
	InputController() : mQuit(nullptr), mnoPtrCurrentController(nullptr)
	{
	}

	inline void Init(InputAction quitAction)
	{
		mQuit = quitAction;
	}

	inline void SetGameController(GameController* controller)
	{
		mnoPtrCurrentController = controller;
	}

	void Update(uint32_t dt);
 private:
	InputAction mQuit;
	GameController* mnoPtrCurrentController;
};

#endif //BREAK_OUT_INPUT_INPUTCONTROLLER_HPP_
