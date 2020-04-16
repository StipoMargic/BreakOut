//
// Created by stipo on 16. 04. 2020..
//

#include "InputController.hpp"
#include <SDL2/SDL.h>
#include "GameController.hpp"

void InputController::Update(uint32_t dt)
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
		{
			mQuit(dt, SDL_PRESSED);
		}
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (mnoPtrCurrentController)
			{
				InputAction action = mnoPtrCurrentController->GetActionForKey(sdlEvent.key.keysym.sym);

				action(dt, static_cast<InputState>(sdlEvent.key.state));
			}
		}
	}
}