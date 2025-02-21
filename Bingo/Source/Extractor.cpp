#include "Extractor.h"
#include "GameState.h"

Extractor::Extractor() : visibleCounter(0), extraCounter(0)
{
	Reset();
}

void Extractor::Reset()
{
	// Draw a new set of balls.
	GameState::Get().RandomizePool();
	auto& poolRef = GameState::Get().GetPool();
	for (int i = 0; i < drawAmmount; ++i)
		balls[i] = poolRef[i];

	// Reset visible balls.
	for (int i = 0; i < drawAmmount; ++i)
		visibleBalls[i] = 0;

	visibleCounter = 0;


	// Deal with extra balls.
	for (int i = 0; i < extraAmmount; ++i)
		extraBalls[i] = poolRef[drawAmmount + i];
		
	for (int i = 0; i < extraAmmount; ++i)
		visibleExtras[i] = 0;

	extraCounter = 0;
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

int Extractor::GetExtra()
{
	if (GameState::Get().GetCredits() > 0 && extraCounter <= extraAmmount - 1)
	{
		GameState::Get().ChangeCredits(-extraCost);
		visibleExtras[extraCounter] = extraBalls[extraCounter];
		return visibleExtras[extraCounter++];
	}

	return -1;
}