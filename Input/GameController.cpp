//
// Created by stipo on 16. 04. 2020..
//

#include "GameController.hpp"

InputAction GameController::GetActionForKey(InputKey key)
{
	for (const auto& ButtonAction : mButtonActions)
	{
		if (key == ButtonAction.key)
		{
			return ButtonAction.action;
		}
	}

	return [](uint32_t, InputState)
	{};
}

void GameController::AddInputActionForKey(const ButtonAction& buttonAction)
{
	mButtonActions.push_back(buttonAction);
}

InputKey GameController::ActionKey()
{
	return static_cast<InputKey>(SDLK_a);
}

InputKey GameController::CancelKey()
{
	return static_cast<InputKey>(SDLK_q);
}

InputKey GameController::LeftKey()
{
	return static_cast<InputKey>(SDLK_LEFT);
}

InputKey GameController::UpKey()
{
	return static_cast<InputKey>(SDLK_UP);
}

InputKey GameController::RightKey()
{
	return static_cast<InputKey>(SDLK_RIGHT);
}

InputKey GameController::DownKey()
{
	return static_cast<InputKey>(SDLK_DOWN);
}

GameController::GameController()
{

}
