#pragma once

#include <array>

class Extractor
{
private:
	static const int drawAmmount = 30;
	std::array<int, drawAmmount> balls;

public:
	Extractor();

	void Draw();

	inline std::array<int, drawAmmount> GetBalls() { return balls; };
};