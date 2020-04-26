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
	ResetGame();

	ButtonAction serveAction;

	serveAction.key = GameController::ActionKey();
	serveAction.action = [this](uint32_t dt, InputState state)
	{
	  if (mGameState == IN_SERVE)
	  {
		  if (GameController::IsPressed(state))
		  {
			  mGameState = IN_PLAY;
			  if (mPaddle.IsMovingLeft())
			  {
				  mBall.SetVelocity(Vec2D(-100, -100));
			  }
			  else
			  {
				  mBall.SetVelocity(Vec2D(100, -100));
			  }
		  }
		  else if (mGameState == GAME_OVER)
		  {
			  if (GameController::IsPressed(state))
			  {
				  ResetGame();
			  }
		  }
	  }
	};

	gameController.AddInputActionForKey(serveAction);

	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state)
	{
	  if (mGameState == IN_SERVE || mGameState == IN_PLAY)
	  {
		  if (GameController::IsPressed(state))
		  {
			  mPaddle.SetMovementDirection(PaddleDirection::LEFT);
		  }
		  else
		  {
			  mPaddle.SetMovementDirection(PaddleDirection::NONE);
		  }
	  }
	};

	gameController.AddInputActionForKey(leftKeyAction);

	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state)
	{
	  if (mGameState == IN_SERVE || mGameState == IN_PLAY)
	  {
		  if (GameController::IsPressed(state))
		  {
			  mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
		  }
		  else
		  {
			  mPaddle.SetMovementDirection(PaddleDirection::NONE);
		  }
	  }
	};
	gameController.AddInputActionForKey(rightKeyAction);
}

void Breakout::Update(uint32_t dt)
{
	if (mGameState == IN_SERVE)
	{
		mPaddle.Update(dt, mBall);
		SetToServeState();
	}
	else if (mGameState == IN_PLAY)
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
			return;
		}

		mLevel.Update(dt, mBall);

		if (IsBallPassedPaddle())
		{
			ReduceLife();
			if (!IsGameOver())
			{
				SetToServeState();
			}
			else
			{
				mGameState = GAME_OVER;
			}
		}
		else if (mLevel.IsLevelComplete())
		{
			ResetGame();
		}
	}
}

void Breakout::Draw(Screen& screen)
{
	mBall.Draw(screen);
	mPaddle.Draw(screen);
	mLevel.Draw(screen);
	screen.Draw(mLevelBoundary.GetAARectangle(), Color::White(), false);

	Circle lifes = { Vec2D(7, App::Singleton().GetHeight() - 10), 5 };

	for (int i = 0; i < mLives; ++i)
	{
		screen.Draw(lifes, Color::Green());
		lifes.MoveBy(Vec2D(17, 0));
	}
}

void Breakout::ResetGame()
{
	mPaddleCutOff = App::Singleton().GetHeight() - 2 * Paddle::PADDLE_HEIGHT;
	mLives = NUM_LIVES;
	AARectangle paddleRect = { Vec2D(App::Singleton().GetWidth() / 2 - Paddle::PADDLE_WIDTH / 2,
		App::Singleton().GetHeight() - 3 * Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT };
	AARectangle boundary = { Vec2D::Zero, App::Singleton().GetWidth(), App::Singleton().GetHeight() };
	mLevelBoundary = { boundary };

	mPaddle.Init(paddleRect, boundary);
	mBall.MoveTo(Vec2D(App::Singleton().GetWidth() / 2, App::Singleton().GetHeight() / 2));
	SetToServeState();
	mLevel.Init(boundary);
}

const std::string& Breakout::GetName()
{
	static std::string name = "Nerdic";
	return name;
}

void Breakout::SetToServeState()
{
	mGameState = IN_SERVE;
	mBall.Stop();
	mBall.MoveTo(Vec2D(mPaddle.GetRectangle().GetCenter().GetX(),
		mPaddle.GetRectangle().GetTopLeft().GetY() - mBall.GetRadius() - 1));
}

bool Breakout::IsBallPassedPaddle() const
{
	return mBall.GetPosition().GetY() > mPaddleCutOff;
}

