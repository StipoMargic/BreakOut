//
// Created by stipo on 16. 04. 2020..
//

#ifndef BREAK_OUT_GAME_GAME_HPP_
#define BREAK_OUT_GAME_GAME_HPP_
#include <string>
#include <cstdint>

class GameController;
class Screen;
class AARectangle;

class Game
{
  public:
    virtual ~Game() {}

    virtual void Init(GameController& gameController, const AARectangle& boundary) = 0;
    virtual void Update(uint32_t dt) = 0;
    virtual void Draw(Screen& screen) = 0;
    virtual const std::string& GetName() = 0;
};

#endif // BREAK_OUT_GAME_GAME_HPP_
