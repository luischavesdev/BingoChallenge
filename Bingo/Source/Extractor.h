#pragma once

#include <array>

class Extractor
{
private:
	static const int drawAmmount = 30;
	std::array<int, drawAmmount> balls;
	std::array<int, drawAmmount> visibleBalls;
	int visibleCounter;

public:
	Extractor();

	void Reset();

	int RevealNextBall();

	void RevealAllBalls();

	inline std::array<int, drawAmmount> GetVisibleBalls() { return visibleBalls; };
	inline int GetDrawAmmount() { return drawAmmount; };
	inline bool IsClear() { return visibleCounter >= drawAmmount; };
};