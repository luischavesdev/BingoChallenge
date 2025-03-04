#include <iostream>
#include <iomanip>
#include <array>

#ifdef LINUX
#include <dlfcn.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#include "Bingo.h"


typedef ProtocolMessage(*interfaceType)();

bool failedInit = false;

const char* prompt1 = "Spend credit (1)    ";
const char* prompt2 = "New card (2)    ";
const char* prompt3 = "Reveal ball (3)    ";
const char* prompt4 = "Reveal all balls (4)    ";
const char* prompt5 = "Cancel (5)    ";
const char* prompt6 = "Exit (6)    ";

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
			std::cout << std::setw(3) << cells[i + j * 3];

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
	void* ptr;

#ifdef LINUX
	ptr = dlsym(lib, funcName);
	auto error = dlerror();
	if (error)
	{
		std::cerr << "Error (when loading the function) " << error << "\n" << std::endl;
		failedInit = true;
	}
		
	dlerror();
#endif

#ifdef WINDOWS
	ptr = (interfaceType)GetProcAddress(HINSTANCE(lib), LPCSTR(funcName));
	if (!ptr)
	{
		std::cerr << "Error (when loading the function) " << GetLastError() << "\n" << std::endl;
		failedInit = true;
	}
		
#endif

	return ptr;
}

int main() {
	void* bingoEngine;

#ifdef LINUX
	bingoEngine = dlopen("./libBingo.so", RTLD_LAZY);
	if (!bingoEngine) 
	{
		std::cerr << "Failed to load the lib.\n" << std::endl;
		failedInit = true;
	}
		
	//interfaceType spendCredits = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "SpendCredits")));
	//interfaceType reshuffleCard = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "ReshuffleCard")));
	//interfaceType revealBall = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "RevealBall")));
	//interfaceType revealBalls = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "RevealBalls")));
	//interfaceType cancelExtras = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "Cancel")));
	//interfaceType exportInfo = reinterpret_cast<interfaceType>(reinterpret_cast<long>(GetFuncPointer(bingoEngine, "ExportInfo")));
#endif

#ifdef WINDOWS
	bingoEngine = LoadLibrary(L"./Bingo.dll");
	if (!bingoEngine)
	{
		std::cerr << "Failed to load the lib.\n" << GetLastError() << std::endl;
		failedInit = true;
	}
#endif

	interfaceType spendCredits = (interfaceType)GetFuncPointer(bingoEngine, "SpendCredits");
	interfaceType reshuffleCard = (interfaceType)GetFuncPointer(bingoEngine, "ReshuffleCard");
	interfaceType revealBall = (interfaceType)GetFuncPointer(bingoEngine, "RevealBall");
	interfaceType revealBalls = (interfaceType)GetFuncPointer(bingoEngine, "RevealBalls");
	interfaceType cancelExtras = (interfaceType)GetFuncPointer(bingoEngine, "Cancel");
	interfaceType exportInfo = (interfaceType)GetFuncPointer(bingoEngine, "ExportInfo");


	char input = '\0';
	int option = 0;
	bool isRunning = true;

	std::cout << "Welcome to console bingo, would you like to play? (y/n)\n";
	std::cin >> input;

	if (failedInit)
	{
		std::cout << "Sorry, couldn't start due to failure on starting the bingo engine.\n";
		input = '\0';
	}

	if (input == 'y')
	{
		Render(exportInfo());

		do
		{
			std::cin >> option;

			// Kinda resets console display on some systems hopefully.
			std::cout << "\033[2J""\033[1;1H";

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

#ifdef LINUX
	dlclose(bingoEngine);
#endif
#ifdef WINDOWS
	FreeLibrary(HINSTANCE(bingoEngine));
#endif

	return 0;
}
