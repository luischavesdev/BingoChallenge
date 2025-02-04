#pragma once

#include <array>
#include <random>

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

	std::random_device randomGenerator;
	std::mt19937 randomEngine;


	GameState();

public:
	static GameState& Get();

	void RandomizePool();

	void AddCredits(const int& value);

	void AddPrizeCredits(const int& patternIndex);

	void BingoAchieved();

	inline std::array<int, universe> GetPool() { return pool; };
	inline static int GetPatternsNumber() { return patternsNumber; };
	inline std::array<short, patternsNumber> GetPatterns() { return patterns; };

	// Singletons do not take copy constructor nor assignment operator.
	GameState(const GameState&) = delete;
	void operator=(const GameState&) = delete;
};