#include "Bingo.h"
#include "GameState.h"
#include "Card.h"
#include "Extractor.h"

Card crd;
Extractor extrct;

void ResetObjects()
{
	crd.Reset();
	extrct.Reset();
}

ProtocolMessage ExportInfo()
{
	ProtocolMessage info;
	info.cells = crd.GetCells();
	info.balls = extrct.GetVisibleBalls();
	info.credits = GameState::Get().GetCredits();
	info.state = GameState::Get().GetState();

	return info;
}

ProtocolMessage SpendCredits()
{
	if (GameState::Get().GetState() == State::S_Down)
	{
		if (GameState::Get().Play())
		{
			ResetObjects();
		}
	}

	return ExportInfo();
}

ProtocolMessage ReshuffleCard()
{
	if (GameState::Get().GetState() == State::S_Shuffle)
	{
		crd.Reset();
	}

	return ExportInfo();
}

ProtocolMessage RevealBall()
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

	return ExportInfo();
}

ProtocolMessage RevealBalls()
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

	return ExportInfo();
}