//#include <iostream>
//#include <dlfcn.h>

#include "Bingo.h"
#include "GameState.h"
#include "Card.h"
#include "Extractor.h"

Card crd;
Extractor extrct;

int* ExportInfo()
{
	// Protocol ended up being a bit messy. Assumed that something if this sort was intended
	int* message = new int[51];
	int counter = 0;

	auto cells = crd.GetCells();
	for (const int& cell : cells)
	{
		message[counter] = cell;
		counter++;
	}

	message[counter] = -1;
	counter++;

	auto balls = extrct.GetVisibleBalls();
	for (const int& ball : balls)
	{
		message[counter] = ball;
		counter++;
	}

	message[counter] = -1;
	counter++;

	message[counter] = GameState::Get().GetCredits();
	counter++;

	message[counter] = -1;
	counter++;

	message[counter] = GameState::Get().GetState();
	counter++;

	message[counter] = -1;
	counter++;

	
	return message;
}

Message MyInfo()
{
	Message info;
	info.cells = crd.GetCells();
	info.balls = extrct.GetVisibleBalls();
	info.credits = GameState::Get().GetCredits();
	info.state = GameState::Get().GetState();

	return info;
}

void SpendCredits()
{
	if (GameState::Get().GetState() == State::S_Down)
	{
		GameState::Get().Play();
	}
}

void ReshuffleCard()
{
	if (GameState::Get().GetState() == State::S_Shuffle)
	{
		crd.Reset();
	}
}

void RevealBall()
{
	switch (GameState::Get().GetState())
	{
	case State::S_Shuffle:
		GameState::Get().DrawState();
	case State::S_Draw:
		crd.CheckHit(extrct.RevealNextBall());

		if (extrct.IsClear())
		{
			GameState::Get().EndPlay();
		}
	}
}

void RevealBalls()
{
	switch (GameState::Get().GetState())
	{
	case State::S_Shuffle:
		GameState::Get().DrawState();
	case State::S_Draw:
		extrct.RevealAllBalls();
		auto balls = extrct.GetVisibleBalls();

		for (const int& ball : balls)
		{
			crd.CheckHit(ball);
		}
		GameState::Get().EndPlay();
	}
}