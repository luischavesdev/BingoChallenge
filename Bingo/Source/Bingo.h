#pragma once
#include <array>

// Extern C is used to query the functions dynamically through name, since it prevents C++ name mangling.
extern "C" void StartCredits(int creditsToAdd);

extern "C" void NewCard();

extern "C" void CheckNumber(int num);

extern "C" std::array<int, 15> GetCard();