//
// Created by stipo on 19. 04. 2020..
//

#include "GameLevel.hpp"

void GameLevel::Init(const AARectangle& boundary)
{
	DefaultLevel(boundary);
}

void GameLevel::Load(const std::vector<Block>& blocks)
{
	mBlocks.clear();
	mBlocks = blocks;
}

void GameLevel::Update(uint32_t dt, Ball& ball)
{
	std::vector<Block> collidedBlocks;

	BoundaryEdge edgeToBounceOffOf;
	Block* noPtrBlockToBounceOffOf = nullptr;

	float largestMag = -1.0f;
	for (auto& block : mBlocks)
	{
		BoundaryEdge edge;
		if (!block.IsDestroyed() && block.HasCollided(ball.GetBoundingRectangle(), edge))
		{
			collidedBlocks.push_back(block);

			float mag = block.GetCollisionOffset(ball.GetBoundingRectangle()).Mag();

			if (mag > largestMag)
			{
				edgeToBounceOffOf = edge;
				noPtrBlockToBounceOffOf = &block;
			}
		}
	}
	if (noPtrBlockToBounceOffOf != nullptr)
	{
		noPtrBlockToBounceOffOf->Bounce(ball, edgeToBounceOffOf);
		noPtrBlockToBounceOffOf->ReduceHP();
	}
	for (const auto& block: collidedBlocks)
	{
		BoundaryEdge edge;
		if (block.HasCollided(ball.GetBoundingRectangle(), edge))
		{
			Vec2D p;
			ball.MakeFlushWithEdge(edge, p, true);
		}
	}
}

void GameLevel::Draw(Screen& screen)
{
	for (auto& block: mBlocks)
	{
		if (!block.IsDestroyed())
		{
			block.Draw(screen);
		}
	}
}

void GameLevel::DefaultLevel(const AARectangle& boundary)
{
	mBlocks.clear();

	const int BLOCK_WIDTH = 16;
	const int BLOCK_HEIGHT = 8;

	const int NUM_BLOCKS_ACROSS = 12;
	const int NUM_BLOCK_ROWS = 5;

	float startX = 4;

	for (int r = 0; r < NUM_BLOCK_ROWS; ++r)
	{
		AARectangle block = { Vec2D(startX, BLOCK_HEIGHT * (r + 1)), BLOCK_WIDTH - 1, BLOCK_HEIGHT - 1 };
		for (int c = 0; c < NUM_BLOCKS_ACROSS; ++c)
		{
			Block b;
			b.Init(block, 1, Color::Red());
			mBlocks.push_back(b);
			block.MoveBy(Vec2D{ BLOCK_WIDTH, 0 });
		}
	}
}

bool GameLevel::IsLevelComplete() const
{
	for (size_t i = 0; i < mBlocks.size(); ++i)
	{
		if (!mBlocks[i].IsDestroyed())
		{
			return false;
		}
	}
	return true;
}


