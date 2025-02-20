#pragma once
#include <array>
#include <random>
#include "Utilities.h"

class GameState
{
private:
	static const int universe = 60;
	// Pool is used to manage an assortment of numbers 1-60 that can be reshuffled and sampled 
	// somewhere else where needed.
	std::array<int, universe> pool;

	static const int patternsNumber = 2;
	// Patterns are represented using 2 bytes. This allows for 16 bits, leaving 1 bit unnused when representing 
	// a 15 cell pattern. The card pattern from top to bottom/left to right, corresponds to the bits sequentially, 
	// from the least significant bit, to the most significant bit (unnused).
	std::array<_16bits, patternsNumber> patterns;
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

	bool Play();

	void AddCredits(const int& value);

	void AddPrizeCredits(const int& patternIndex);

	void BingoAchieved();

	void DrawState();

	void EndPlay(bool extra = false);

	inline std::array<int, universe> GetPool() { return pool; };
	inline int GetPatternsNumber() { return patternsNumber; };
	inline std::array<_16bits, patternsNumber> GetPatterns() { return patterns; };
	inline int GetCredits() { return credits; };
	inline State GetState() { return currentState; };

	// Singletons do not take copy constructor nor assignment operator.
	GameState(const GameState&) = delete;
	void operator=(const GameState&) = delete;
};