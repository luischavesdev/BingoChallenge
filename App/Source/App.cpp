#include <iostream>
#include <array>
#include <random>
#include <iomanip>
#include <algorithm>

const int universe = 60;
std::array<int, universe> pool;

std::random_device randomGenerator;
std::mt19937 randomEngine(randomGenerator());



void RandomizePool()
{
	std::shuffle(pool.begin(), pool.end(), randomEngine);
}

void Initialization()
{
	for (int i = 0; i < universe; ++i) {
		pool[i] = i + 1;
	}

	RandomizePool();
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

	template<int N>
	void CheckHits(std::array<int, N> balls)
	{
		for (const int& ball : balls)
		{
			auto hit = std::find(cells.begin(), cells.end(), ball);
			if (hit != cells.end())
			{
				*hit = 0;
			}
		}

		RenderCard();
	}


private:
	std::array<int, size> cells;

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
		for (int i = 0; i < drawAmmount; ++i)
		{
			RandomizePool();
			balls[i] = pool[i];
		}

		RenderDraw();
	}

	void RenderDraw()
	{
		for (const int& ball : balls)
		{
			std::cout << ball << '\n';
		}
		std::cout << '\n';
	}

private:


};


int main() {
	Initialization();

	int credits = 1;
	int maxCredits = 999;
	int addedCredits = 0;

	char input = '\0';

	Card crd = Card();
	Extractor ex = Extractor();


	std::cout << "How many credits to start?\n";
	std::cin >> addedCredits;
	credits = std::max(0, std::min(credits + addedCredits, maxCredits));
	std::cout << "Proceed to show card. (y)\n";
	std::cin >> input;
	
	do
	{
		crd.ReshuffleCells();
		std::cout << "Generate another card? (y/n)\n";
		std::cin >> input;
	} while (!std::cin.fail() && (input == 'y'));

	
	std::cout << "Draw balls. (y)\n";
	std::cin >> input;
	ex.Draw();

	//crd.CheckHits(ex.balls);


	std::cin.get();





}