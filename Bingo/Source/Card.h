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


	/*void RenderCard()
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				std::cout << std::setw(3) << cells[j + i * columns];
			}

			std::cout << '\n';
		}

		std::cout << '\n';
	}*/

public:
	Card();

	void PopulateCells();

	void CheckHit(const int& ball);

	template<int N>
	void CheckHits(const std::array<int, N>& balls) { for (const int& ball : balls) CheckHit(ball); }

	inline std::array<int, 15> GetCells() { return cells; };
};