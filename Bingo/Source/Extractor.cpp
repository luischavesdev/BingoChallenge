#include "Extractor.h"
#include "GameState.h"

Extractor::Extractor()
{
	Draw();
}

void Extractor::Draw()
{
	GameState::Get().RandomizePool();
	auto poolCopy = GameState::Get().GetPool();
	for (int i = 0; i < drawAmmount; ++i)
	{
		balls[i] = poolCopy[i];
	}
}