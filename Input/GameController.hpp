//
// Created by stipo on 16. 04. 2020..
//

#ifndef BREAK_OUT_INPUT_GAMECONTROLLER_HPP_
#define BREAK_OUT_INPUT_GAMECONTROLLER_HPP_

#include "InputAction.hpp"
#include <vector>
#include <SDL2/SDL.h>

class GameController
{
 public:
	GameController();
	InputAction GetActionForKey(InputKey key);
	void AddInputActionForKey(const ButtonAction& buttonAction);

	inline void ClearAll()
	{
		mButtonActions.clear();
	}
	// Hide SDL Implementation

	inline static bool IsPressed(InputState state)
	{
		return state == SDL_PRESSED;
	}

	inline static bool IsReleased(InputState state)
	{
		return state == SDL_RELEASED;
	}

	// Our Keys
	static InputKey ActionKey(); // Do something
	static InputKey CancelKey(); // Cancel Something
	static InputKey LeftKey();
	static InputKey UpKey();
	static InputKey RightKey();
	static InputKey DownKey();
 private:
	std::vector<ButtonAction> mButtonActions;
};

#endif //BREAK_OUT_INPUT_GAMECONTROLLER_HPP_
