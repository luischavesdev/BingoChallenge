#include <algorithm>
#include "GameState.h"

GameState::GameState() : patterns({ 0b0001000111011111, 0b0111110010011111 }), patternsPrizes({ 10, 50 }),
bingoPrize(100), credits(1), maxCredits(999)
{
	randomEngine.seed(randomGenerator());

	for (int i = 0; i < universe; ++i) {
		// The +1 is to register values in the [1, 60] range instead of [0, 59].
		pool[i] = i + 1;
	}

	RandomizePool();
}

GameState& GameState::Get()
{
	static GameState instance;
	return instance;
}

void GameState::RandomizePool()
{
	std::shuffle(pool.begin(), pool.end(), randomEngine);
}

void GameState::AddCredits(const int& value)
{
	credits = std::max(0, std::min(credits + value, maxCredits));
}

void GameState::AddPrizeCredits(const int& value)
{
	AddCredits(patternsPrizes[value]);
}

void GameState::BingoAchieved()
{
	AddCredits(bingoPrize);
}