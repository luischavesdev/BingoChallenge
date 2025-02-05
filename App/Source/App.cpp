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





void Render(const ProtocolMessage& message)
{
	std::cout << "\n";
	std::cout << "Current play state. Card:\n";

	auto& cells = message.cells;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			std::cout << std::setw(3) << cells[j + i * 5];
		}

		std::cout << '\n';
	}

	std::cout << "\n";
	std::cout << "Balls:\n";

	auto& balls = message.balls;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			std::cout << std::setw(3) << balls[j + i * 6];
		}

		std::cout << '\n';
	}

	std::cout << "\n";
	std::cout << "Credits: " << message.credits << "\n";
	std::cout << "\n";


	switch (message.state)
	{
	case 0:
		std::cout << "Play (1)    " << "Exit (5)\n";
		break;
	case 1:
		std::cout << "New card (2)    " << "Reveal ball (3)    " << "Reveal all balls (4)    " << "Exit (5)\n";
		break;
	case 2:
		std::cout << "Reveal ball (3)    " << "Reveal all balls (4)    " << "Exit (5)\n";
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
