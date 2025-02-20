#include <algorithm>
#include "GameState.h"

GameState::GameState() : patterns({ 0b0001011111011001, 0b0101101111101101 }), patternsPrizes({ 10, 50 }),
bingoPrize(100), credits(100), maxCredits(999), playCost(1), currentState(State::S_Down)
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

bool GameState::Play()
{
	if (currentState == State::S_Down && credits >= playCost)
	{
		currentState = State::S_Shuffle;
		AddCredits(-playCost);
		return true;
	}
	return false;
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

void GameState::DrawState()
{
	currentState = State::S_Draw;
}

void GameState::EndPlay(bool extra)
{
	if (extra)
		currentState = State::S_Extra;
	else
		currentState = State::S_Down;
}