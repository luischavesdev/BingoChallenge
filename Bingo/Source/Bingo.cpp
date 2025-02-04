//#include <iostream>
//#include <dlfcn.h>

#include "Bingo.h"
#include "GameState.h"
#include "Card.h"
#include "Extractor.h"

Card crd;
Extractor extrct;

void StartCredits(int creditsToAdd)
{
	GameState::Get().AddCredits(creditsToAdd);
}

void NewCard()
{
	crd.PopulateCells();
}

void CheckNumber(int num)
{
	crd.CheckHit(num);
}

std::array<int, 15> GetCard()
{
	crd.GetCells();
}
