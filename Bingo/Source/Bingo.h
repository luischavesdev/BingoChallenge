#pragma once
#include <array>

struct Message
{
	std::array<int, 15> cells;
	std::array<int, 30> balls;
	int credits;
	int state;
};

// Extern C is used to query the functions dynamically through name, since it prevents C++ name mangling.
// Reports back the overall state of the game so that it can be rendered.
extern "C" int* ExportInfo();

// These encompass all the input that the player needs to communicate with the game.
extern "C" void SpendCredits();

extern "C" void ReshuffleCard();

extern "C" void RevealBall();

extern "C" void RevealBalls();

extern "C" Message MyInfo();