#pragma once
#include <array>

class Extractor
{
private:
	static const int drawAmmount = 30;
	std::array<int, drawAmmount> balls;
	std::array<int, drawAmmount> visibleBalls;
	int visibleCounter;

	static const int extraAmmount = 3;
	static const int extraCost = 1;
	std::array<int, extraAmmount> extraBalls;
	std::array<int, extraAmmount> visibleExtras;
	int extraCounter;

public:
	Extractor();

	void Reset();

	int RevealNextBall();

	void RevealAllBalls();

	int GetExtra();

	inline std::array<int, drawAmmount>& GetVisibleBalls() { return visibleBalls; };
	inline std::array<int, extraAmmount>& GetVisibleExtras() { return visibleExtras; };
	inline int GetDrawAmmount() { return drawAmmount; };
	inline bool IsClear() { return visibleCounter >= drawAmmount; };
	inline bool IsExtraless() { return extraCounter >= extraAmmount; };
};