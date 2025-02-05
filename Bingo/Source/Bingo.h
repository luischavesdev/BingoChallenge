#pragma once
#include <array>

// Protocol is a simple struct with the data that is needed to inform the player. Not sure if this is valid, or 
// if the expected approach was to go all in raw, and send an int* that the client then had to parse until a 
// null termination character was found, or something of that sort.
struct ProtocolMessage
{
	std::array<int, 15> cells;
	std::array<int, 30> balls;
	std::array<int, 3> extraBalls;
	int credits;
	int state;
};

// Extern C is used to query the functions dynamically through name, since it prevents C++ name mangling.
// Reports back the overall state of the game so that it can be rendered. (Output)
extern "C" ProtocolMessage ExportInfo();

// These others encompass all the input that the player needs to communicate with the game. (Input)
extern "C" ProtocolMessage SpendCredits();

extern "C" ProtocolMessage ReshuffleCard();

extern "C" ProtocolMessage RevealBall();

extern "C" ProtocolMessage RevealBalls();

extern "C" ProtocolMessage Cancel();