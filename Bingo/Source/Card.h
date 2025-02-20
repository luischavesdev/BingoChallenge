#pragma once
#include <array>
#include "Utilities.h"

class Card
{
private:
	static const int rows = 3;
	static const int columns = 5;
	static const int size = rows * columns;

	std::array<int, size> cells;
	_16bits hitState;

	int patternsCompleted;
	int hitCounter;

	void PopulateCells();

public:
	Card();

	void Reset();

	void CheckHit(const int& ball);

	inline std::array<int, size> GetCells() { return cells; };
};