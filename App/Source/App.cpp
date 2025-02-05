#include <iostream>
#include <iomanip>
#include <array>
#include <dlfcn.h>
#include "Bingo.h"


typedef ProtocolMessage(*interfaceType)();

char* prompt1 = "Spend credit (1)    ";
char* prompt2 = "New card (2)    ";
char* prompt3 = "Reveal ball (3)    ";
char* prompt4 = "Reveal all balls (4)    ";
char* prompt5 = "Cancel (5)    ";
char* prompt6 = "Exit (6)    ";

void Render(const ProtocolMessage& message)
{
	static int lastState = 0;

	// Starter message
	if (message.state == 0)
		std::cout << "\n\nInsert credit!\n";
	else
		std::cout << "\n\nCurrent play state.\n";

	// Card
	std::cout << "Card:\n";
	auto& cells = message.cells;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
			std::cout << std::setw(3) << cells[j + i * 5];

		std::cout << '\n';
	}

	// Balls
	std::cout << "\nBalls:\n";
	auto& balls = message.balls;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 6; ++j)
			std::cout << std::setw(3) << balls[j + i * 6];

		std::cout << '\n';
	}

	// Extra balls
	if (message.state == 3 || lastState == 3)
	{
		std::cout << "\nExtra Balls:\n";

		auto& extras = message.extraBalls;
		for (int i = 0; i < 3; ++i)
			std::cout << std::setw(3) << extras[i];

		std::cout << '\n';
	}

	// Credits
	std::cout << "\nCredits: " << message.credits << "\n\n";

	// Input
	switch (message.state)
	{
	case 0:
		std::cout << prompt1 << prompt6 << "\n";
		break;
	case 1:
		std::cout << prompt2 << prompt3 << prompt4 << prompt6 << "\n";
		break;
	case 2:
		std::cout << prompt3 << prompt4 << prompt6 << "\n";
		break;
	case 3:
		std::cout << prompt1 << prompt5 << prompt6 << "\n";
		break;
	default:
		std::cout << "Error state!\n";
	}

	std::cout << "\n";

	lastState = message.state;
}

void* GetFuncPointer(void* lib, const char* funcName)
{
	void* ptr = dlsym(lib, funcName);
	auto error = dlerror();
	if (error)
		std::cerr << "Error (when loading the function) " << error << std::endl;

	dlerror();
	return ptr;
}

int main() {
	void* bingoEngine = dlopen("./libBingo.so", RTLD_LAZY);
	if (!bingoEngine)
		std::cerr << "Failed to load the lib. " << std::endl;

	interfaceType spendCredits = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "SpendCredits")));
	interfaceType reshuffleCard = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "ReshuffleCard")));
	interfaceType revealBall = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "RevealBall")));
	interfaceType revealBalls = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "RevealBalls")));
	interfaceType cancelExtras = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "Cancel")));
	interfaceType exportInfo = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "ExportInfo")));

	
	char input = '\0';
	int option = 0;
	bool isRunning = true;

	std::cout << "Welcome to console bingo, would you like to play? (y/n)\n";
	std::cin >> input;

	if (input == 'y')
	{
		Render(exportInfo());

		do
		{
			std::cin >> option;

			switch (option)
			{
			case 1:
				Render(spendCredits());
				break;
			case 2:
				Render(reshuffleCard());
				break;
			case 3:
				Render(revealBall());
				break;
			case 4:
				Render(revealBalls());
				break;
			case 5:
				Render(cancelExtras());
				break;
			case 6:
				isRunning = false;
				break;
			default:
				std::cout << "Not valid input.\n";
			}

		} while (isRunning);
	}

	std::cout << "See ya!\n";

	dlclose(bingoEngine);
	return 0;
}
