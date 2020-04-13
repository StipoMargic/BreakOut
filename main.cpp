#include <SDL2/SDL.h>
#include <iostream>
#include <Color.hpp>
#include <Screen.hpp>
#include <Line2D.hpp>

using namespace std;

int main()
{
	Screen screen;

	screen.Init(200, 200, 3);

	screen.Draw(100, 105, Color::Blue());
	screen.Draw(Line2D(Vec2D(0,100), Vec2D(200,100)), Color::Red());
	screen.SwitchScreens();

	SDL_Event sdlEvent;
	bool isOpen = true;

	while (isOpen)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
				case SDL_QUIT:isOpen = false;
					break;
			}
		}
	}

	return 0;
}
