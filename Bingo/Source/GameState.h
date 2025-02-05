#pragma once

#include <array>
#include <random>
#include "StateEnum.h"

class GameState
{
private:
	static const int universe = 60;
	// Pool is used to manage an assortment of numbers 1-60 that can be reshuffled and sampled 
	// somewhere else where needed.
	std::array<int, universe> pool;

	static const int patternsNumber = 2;
	std::array<short, patternsNumber> patterns;
	std::array<int, patternsNumber> patternsPrizes;
	int bingoPrize;

	int credits;
	int maxCredits;
	int playCost;

	std::random_device randomGenerator;
	std::mt19937 randomEngine;

	State currentState;


	GameState();

public:
	static GameState& Get();

	void RandomizePool();

	void Play();

	void AddCredits(const int& value);

	void AddPrizeCredits(const int& patternIndex);

	void BingoAchieved();

	void DrawState();

	void EndPlay();

	inline std::array<int, universe> GetPool() { return pool; };
	inline int GetPatternsNumber() { return patternsNumber; };
	inline std::array<short, patternsNumber> GetPatterns() { return patterns; };
	inline int GetCredits() { return credits; };
	inline State GetState() { return currentState; };

	// Singletons do not take copy constructor nor assignment operator.
	GameState(const GameState&) = delete;
	void operator=(const GameState&) = delete;
};