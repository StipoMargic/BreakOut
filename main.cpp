#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main() {

    if (SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Sh?t happened!" << endl;
        return 1;
    }

    SDL_Window *oPtrWindow = SDL_CreateWindow("Nerdic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200, 0);

    if (oPtrWindow == nullptr) {
        cout << "Sh?t happened again!" << SDL_GetError() << endl;
        return 1;
    }

    SDL_Event sdlEvent;
    bool isOpen = true;

    while (isOpen) {
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    isOpen = false;
                    break;
            }
        }
    }

    SDL_DestroyWindow(oPtrWindow);
    SDL_Quit();
    return 0;
}