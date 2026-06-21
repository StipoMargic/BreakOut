//
// Created by stipo on 17. 04. 2020..
//

#include "Breakout.hpp"
#include "InputAction.hpp"
#include "GameController.hpp"
#include <cstdint>

void Breakout::Init(GameController& gameController, const AARectangle& boundary)
{
	mBoundary = boundary;
	ResetGame();

	ButtonAction serveAction;

	serveAction.key = GameController::ActionKey();
	serveAction.action = [this](uint32_t dt, InputState state)
	{
	  if (!GameController::IsPressed(state))
	  {
		  return;
	  }

	  if (mGameState == IN_SERVE)
	  {
		  mGameState = IN_PLAY;
		  if (mPaddle.IsMovingLeft())
		  {
			  mBall.SetVelocity(Vec2D(-INITIAL_VELOCITY.GetX(), INITIAL_VELOCITY.GetY()));
		  }
		  else
		  {
			  mBall.SetVelocity(INITIAL_VELOCITY);
		  }
	  }
	  else if (mGameState == GAME_OVER)
	  {
		  ResetGame();
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

		if (mLevelBoundary.HasCollided(mBall, edge))
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

	Circle lifes = { Vec2D(7, mBoundary.GetHeight() - 10), 5 };

	for (int i = 0; i < mLives; ++i)
	{
		screen.Draw(lifes, Color::Green());
		lifes.MoveBy(Vec2D(17, 0));
	}
}

void Breakout::ResetGame()
{
	mPaddleCutOff = mBoundary.GetHeight() - 2 * Paddle::PADDLE_HEIGHT;
	mLives = NUM_LIVES;
	AARectangle paddleRect = { Vec2D(mBoundary.GetWidth() / 2 - Paddle::PADDLE_WIDTH / 2,
		mBoundary.GetHeight() - 3 * Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT };
	mLevelBoundary = { mBoundary };

	mPaddle.Init(paddleRect, mBoundary);
	mBall.MoveTo(Vec2D(mBoundary.GetWidth() / 2, mBoundary.GetHeight() / 2));
	SetToServeState();
	mLevel.Init(mBoundary);
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

