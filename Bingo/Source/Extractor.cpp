#include "Extractor.h"
#include "GameState.h"

Extractor::Extractor() : visibleCounter(0)
{
	Reset();
}

void Extractor::Reset()
{
	// Draw a new set of balls.
	GameState::Get().RandomizePool();
	auto poolCopy = GameState::Get().GetPool();
	for (int i = 0; i < drawAmmount; ++i)
	{
		balls[i] = poolCopy[i];
	}

	// Reset visible balls.
	for (int i = 0; i < drawAmmount; ++i) {
		visibleBalls[i] = 0;
	}
	visibleCounter = 0;
}

int Extractor::RevealNextBall()
{
	if (visibleCounter <= drawAmmount - 1)
	{
		visibleBalls[visibleCounter] = balls[visibleCounter];
		return visibleBalls[visibleCounter++];
	}

	return -1;
}

void Extractor::RevealAllBalls()
{
	for (int i = 0; i < drawAmmount; ++i)
	{
		visibleBalls[i] = balls[i];
	}
	visibleCounter = drawAmmount - 1;
}