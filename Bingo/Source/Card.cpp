#include <algorithm>
#include "Card.h"
#include "GameState.h"

Card::Card() : hitState(0), patternsCompleted(0), hitCounter(0)
{
	for (int i = 0; i < size; ++i)
	{
		// PopulateCells needs to be explicitly called, otherwise cells will be at zero.
		cells[i] = 0;
	}
}

void Card::PopulateCells()
{
	GameState::Get().RandomizePool();
	auto& poolRef = GameState::Get().GetPool();

	for (int i = 0; i < size; ++i)
	{
		cells[i] = poolRef[i];
	}

	std::sort(cells.begin(), cells.end());
}

void Card::Reset()
{
	PopulateCells();
	hitState.reset();
	patternsCompleted = 0;
	hitCounter = 0;
}

void Card::CheckHit(const int& ball)
{
	auto hit = std::find(cells.begin(), cells.end(), ball);
	// If the ball value was not found, std::find returns the end iterator.
	if (hit != cells.end())
	{
		// A 0 replaces the cell number to visualize the hit when printing the card to console.
		*hit = 0;
		hitCounter++;

		int numberOfPatterns = GameState::Get().GetPatternsNumber();

		if (patternsCompleted < numberOfPatterns)
		{
			int index = std::distance(cells.begin(), hit);
			// Creating a bit mask to highlight the index of the matched number.
			patternbits mask;
			mask.set(index);
				
			hitState = hitState | mask;

			auto& patternsRef = GameState::Get().GetPatterns();

			for (int i = 0; i < numberOfPatterns; ++i)
			{
				if ((hitState & patternsRef[i]) == patternsRef[i])
				{
					patternsCompleted++;
					// Not sure if both prizes should be awarded due to a single ball, instead of choosing the biggest.
					GameState::Get().AddPrizeCredits(i);
				}
			}
		}

		if (hitCounter == size)
		{
			GameState::Get().BingoAchieved();
		}
	}
}