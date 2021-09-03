#include "Rocket.h"
#include <SFML/Graphics.hpp>


#pragma once
class Game
{

public:
	Game();
	Game(int score):
		score(score)
	{
	}

private:
public:
int altitude = 0;
private:
	int score;
};
