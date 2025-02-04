#include <iostream>
#include <array>
#include <random>
#include <iomanip>
#include <algorithm>

const int universe = 60;
// Pool is used to manage an assortment of numbers 1-60 that can be reshuffled and sampled somewhere else where needed.
std::array<int, universe> pool;

const int patternsNumber = 2;
const std::array<short, patternsNumber> patterns = { 0b0001000111011111, 0b0111110010011111 };
const std::array<int, patternsNumber> patternsPrizes = { 10, 50 };
const int bingoPrize = 100;

int credits = 1;
const int maxCredits = 999;

std::random_device randomGenerator;
std::mt19937 randomEngine(randomGenerator());


void RandomizePool()
{
	std::shuffle(pool.begin(), pool.end(), randomEngine);
}

void Initialization()
{
	for (int i = 0; i < universe; ++i) {
		// The +1 is to register values in the [1, 60] range instead of [0, 59].
		pool[i] = i + 1;
	}

	RandomizePool();
}

void AddCredits(const int& value)
{
	credits = std::max(0, std::min(credits + value, maxCredits));
}


class Card
{
public:
	static const int rows = 3;
	static const int columns = 5;
	static const int size = rows * columns;

	Card(const bool& populate = false)
	{
		if (populate)
		{
			PopulateCells();
		}
	}

	void ReshuffleCells()
	{
		RandomizePool();
		PopulateCells();
	}

	void CheckHit(const int& ball, const bool& render = false)
	{
		std::cout << "Ball: " << ball << '\n';
		auto hit = std::find(cells.begin(), cells.end(), ball);
		// If the ball value was not found, find returns the end iterator.
		if (hit != cells.end())
		{
			// A 0 replaces the cell number to visualize the hit when printing the card to console.
			*hit = 0;
			std::cout << "Hit!" << '\n';
			hitNumber++;

			if (patternsCompleted < patternsNumber)
			{
				int index = std::distance(cells.begin(), hit);
				// Creating a bit mask to highlight the index of the matched number.
				short mask = 1;
				mask <<= index;

				hitState = hitState | mask;

				for (int i = 0; i < patternsNumber; ++i)
				{
					if ((hitState & patterns[i]) == patterns[i] && !patternsCompletion[i])
					{
						patternsCompletion[i] = true;
						patternsCompleted++;
						// Not sure if both prizes should be awarded due to a single ball, instead of choosing the biggest.
						AddCredits(patternsPrizes[i]);
						std::cout << "Pattern completed! You won " << patternsPrizes[i] << " credits." << '\n';
					}
				}
			}

			if (hitNumber == size)
			{
				std::cout << "Bingo!\n";
				AddCredits(bingoPrize);
			}

			if (render)
				RenderCard();
		}
	}

	//template<int N>
	void CheckHits(const std::array<int, 30>& balls)
	{
		for (const int& ball : balls)
		{
			CheckHit(ball);
		}

		RenderCard();
	}


private:
	std::array<int, size> cells;
	short hitState = 0b0000000000000000;
	// Just for sanity check.
	std::array<bool, patternsNumber> patternsCompletion = { false, false };
	int patternsCompleted = 0;
	int hitNumber = 0;

	void PopulateCells()
	{
		for (int i = 0; i < size; ++i)
		{
			cells[i] = pool[i];
		}

		RenderCard();
	}

	void RenderCard()
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
	}
};


class Extractor
{
public:
	static const int drawAmmount = 30;
	std::array<int, drawAmmount> balls;

	void Draw()
	{
		RandomizePool();
		for (int i = 0; i < drawAmmount; ++i)
		{
			balls[i] = pool[i];
		}
	}
};


int main() {



	Initialization();
	bool endGame = false;
	char input = '\0';

	int addedCredits = 0;
	std::cout << "How many credits to add?\n";
	std::cin >> addedCredits;
	AddCredits(addedCredits);

	do
	{
		std::cout << "You have " << credits << " credits. Play? (y/n)\n";
		std::cin >> input;

		if (input == 'y')
		{
			if (credits <= 0)
			{
				std::cout << "Not enough credits. Try again.\n";
				break;
			}

			credits--;
			Card crd = Card();
			Extractor ex = Extractor();

			do
			{
				crd.ReshuffleCells();
				std::cout << "Generate another card? (y/n)\n";
				std::cin >> input;
			} while (!std::cin.fail() && (input == 'y'));

			std::cout << "Draw balls. (y)\n";
			std::cin >> input;
			ex.Draw();

			std::cout << "Check all hits at once? (y/n)\n";
			std::cin >> input;

			if (input == 'y')
			{
				crd.CheckHits(ex.balls);
			}
			else
			{
				int ammount = ex.balls.size();
				for (int i = 0; i < ammount; ++i)
				{
					/*int debugNum = 0;
					std::cout << "Input Number. (y)\n";
					std::cin >> debugNum;
					crd.CheckHit(debugNum);*/

					crd.CheckHit(ex.balls[i], true);
					if (i == ammount - 1)
					{
						std::cout << "That's all. (y)\n";
						std::cin >> input;
					}
					else
					{
						std::cout << "Check next ball. (y)\n";
						std::cin >> input;
					}
				}
			}

			std::cout << "Play again? (y/n)\n";
			std::cin >> input;

			if (input == 'n')
				endGame = true;
		}
		else
		{
			endGame = true;
		}
	} while (!endGame);



	std::cin.get();
}
