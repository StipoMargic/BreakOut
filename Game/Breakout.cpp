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

	gameController.AddInputActionForKey(leftKeyAction);

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
	gameController.AddInputActionForKey(rightKeyAction);
}

void Breakout::Update(uint32_t dt)
{
	mBall.Update(dt);
	mPaddle.Update(dt, mBall);

	BoundaryEdge edge;

	if (mPaddle.Bounce(mBall))
	{
		return;
	}

	if (mLevelBoundary.HasCollied(mBall, edge))
	{
		mBall.Bounce(edge);
	}
}

void Breakout::Draw(Screen& screen)
{
	mBall.Draw(screen);
	mPaddle.Draw(screen);
}

void Breakout::ResetGame()
{
	AARectangle paddleRect = { Vec2D(App::Singleton().GetWidth() / 2 - Paddle::PADDLE_WIDTH / 2,
		App::Singleton().GetHeight() - 3 * Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT };
	AARectangle boundary = { Vec2D::Zero, App::Singleton().GetWidth(), App::Singleton().GetHeight() };
	mLevelBoundary = { boundary };

	mPaddle.Init(paddleRect, boundary);
	mBall.MoveTo(Vec2D(App::Singleton().GetWidth() / 2, App::Singleton().GetHeight() / 2));
	mBall.SetVelocity(INITIAL_VELOCITY);
}

const std::string& Breakout::GetName()
{
	static std::string name = "Nerdic";
	return name;
}

