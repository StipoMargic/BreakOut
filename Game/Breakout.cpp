//
// Created by stipo on 17. 04. 2020..
//

#include "Breakout.hpp"
#include "InputAction.hpp"
#include "GameController.hpp"
#include "App.hpp"
#include <cstdint>

void Breakout::Init(GameController& gameController)
{
	ButtonAction leftKeyAction;
	ResetGame();
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state)
	{
	  if (GameController::IsPressed(state))
	  {
		  mPaddle.SetMovementDirection(PaddleDirection::LEFT);
	  }
	  else
	  {
		  mPaddle.SetMovementDirection(PaddleDirection::NONE);
	  }
	};

	gameController.AddInputActionForKy(leftKeyAction);

	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state)
	{
	  if (GameController::IsPressed(state))
	  {
		  mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
	  }
	  else
	  {
		  mPaddle.SetMovementDirection(PaddleDirection::NONE);
	  }
	};
	gameController.AddInputActionForKy(rightKeyAction);
}

void Breakout::Update(uint32_t dt)
{
	mPaddle.Update(dt);
}

void Breakout::Draw(Screen& screen)
{
	mPaddle.Draw(screen);
}

void Breakout::ResetGame()
{
	AARectangle paddleRect = { Vec2D(App::Singleton().GetWidth() / 2 - Paddle::PADDLE_WIDTH / 2,
		App::Singleton().GetHeight() - 3 * Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT };
	AARectangle boundary = { Vec2D::Zero, App::Singleton().GetWidth(), App::Singleton().GetHeight() };

	mPaddle.Init(paddleRect, boundary);
}

