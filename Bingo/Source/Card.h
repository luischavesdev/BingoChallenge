#pragma once

#include <array>

class Card
{
private:
	static const int rows = 3;
	static const int columns = 5;
	static const int size = rows * columns;

	std::array<int, size> cells;
	short hitState;

	int patternsCompleted;
	int hitCounter;

	void PopulateCells();

public:
	Card();

	void Reset();

	void CheckHit(const int& ball);

	inline std::array<int, size> GetCells() { return cells; };
};