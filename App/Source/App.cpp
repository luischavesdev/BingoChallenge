#include <iostream>
#include <iomanip>
#include <array>
#include <dlfcn.h>
#include "Bingo.h"


//typedef void (*signature1)();
//typedef void (*signature2)(int);
//typedef std::array<int, 15> (*signature3)();

//void (*newCardPtr)();
//void (*checkNumPtr)(int);
//std::array<int, 15> (*getCrdPtr)();
//int (*addPtr)(int);




//void* ptr0 = dlsym(bingoEngine, "increase_num");


//void* bingoEngine = dlopen("./bingoengine.so", RTLD_LAZY);
//if (!bingoEngine)
//std::cout << "Failed to load the lib.\n";
//else
//std::cout << "Load the lib!\n";
//
//
//
//
//
//auto ptr0 = dlsym(bingoEngine, "StartCredits");
//auto error0 = dlerror();
//if (error0) {
//	std::cerr << "Error (when loading the symbol `func0`): " << error0 << std::endl;
//}
//dlerror();
//
//typedef void (*ptrType0)(int);
//ptrType0 startCreditsPtr = reinterpret_cast<ptrType0>(reinterpret_cast<long>(ptr0));
//
//if (startCreditsPtr != nullptr)
//std::cout << "Load the func0!\n";
//
//
//
//
//auto ptr1 = dlsym(bingoEngine, "NewCard");
//auto error1 = dlerror();
//if (error1) {
//	std::cerr << "Error (when loading the symbol `func1`): " << error1 << std::endl;
//}
//dlerror();
//
//typedef void (*ptrType1)();
//ptrType1 newCardPtr = reinterpret_cast<ptrType1>(reinterpret_cast<long>(ptr1));
//
//if (newCardPtr != nullptr)
//std::cout << "Load the func1!\n";
//
//
//
//auto ptr2 = dlsym(bingoEngine, "CheckNumber");
//auto error2 = dlerror();
//if (error2) {
//	std::cerr << "Error (when loading the symbol `func2`): " << error2 << std::endl;
//}
//dlerror();
//
//typedef void (*ptrType2)(int);
//ptrType2 checkNumberPtr = reinterpret_cast<ptrType2>(reinterpret_cast<long>(ptr2));
//
//if (checkNumberPtr != nullptr)
//std::cout << "Load the func2!\n";
//
//
//
//auto ptr3 = dlsym(bingoEngine, "GetCard");
//auto error3 = dlerror();
//if (error3) {
//	std::cerr << "Error (when loading the symbol `func3`): " << error3 << std::endl;
//}
//dlerror();
//
//typedef std::array<int, 15>(*ptrType3)();
//ptrType3 getCardPtr = reinterpret_cast<ptrType3>(reinterpret_cast<long>(ptr3));
//
//if (getCardPtr != nullptr)
//std::cout << "Load the func3!\n";



//dlclose(bingoEngine);



char* prompt1 = "Spend credit (1)    ";
char* prompt2 = "New card (2)    ";
char* prompt3 = "Reveal ball (3)    ";
char* prompt4 = "Reveal all balls (4)    ";
char* prompt5 = "Cancel (5)    ";
char* prompt6 = "Exit (6)    ";

void Render(const ProtocolMessage& message)
{
	// Starter message
	if (message.state == 0)
		std::cout << "\nInsert credit!\n";
	else
		std::cout << "\nCurrent play state.\n";

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
	if (message.state == 3)
	{
		std::cout << "\nExtra Balls:\n";

		auto& extras = message.extraBalls;
		for (int i = 0; i < 3; ++i)
			std::cout << std::setw(3) << extras[i];

		std::cout << '\n';
	}

	// Credits
	std::cout << "\nCredits: " << message.credits << "\n";

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
}

int main() {
	char input = '\0';
	int option = 0;
	bool isRunning = true;

	std::cout << "Welcome to console bingo, would you like to play? (y/n)\n";
	std::cin >> input;

	if (input == 'y')
	{
		Render(ExportInfo());

		do
		{
			std::cin >> option;

			switch (option)
			{
			case 1:
				Render(SpendCredits());
				break;
			case 2:
				Render(ReshuffleCard());
				break;
			case 3:
				Render(RevealBall());
				break;
			case 4:
				Render(RevealBalls());
				break;
			case 5:
				Render(Cancel());
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
	std::cin >> input;	
}
