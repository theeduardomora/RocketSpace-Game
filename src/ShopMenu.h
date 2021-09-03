#include "Rocket.h"
#include <SFML/Graphics.hpp>

#pragma once

//using namespace sf;

class ShopMenu
{

public:
	ShopMenu(Rocket& rocket) :
		rocket(rocket)
	{}

	sf::Color get_FTupgradeboxt()
	{

		if (rocket.get_FTUPNUM() == 0)
		{
			sf::Color color(150, 219, 138);
			return color;
		}
		else if (rocket.get_FTUPNUM() == 1)
		{
			sf::Color color(149, 219, 138);
			return color;
		}
		else
		{
			sf::Color color(151, 219, 138);
			return color;
		}
	}

	sf::Color get_BRupgradeboxt()
	{

		if (rocket.get_BRUPNUM() == 0)
		{
			sf::Color color(150, 218, 138);
			return color;
		}
		else if (rocket.get_BRUPNUM() == 1)
		{
			sf::Color color(150, 220, 138);
			return color;
		}
		else
		{
			sf::Color color(150, 221, 138);
			return color;
		}
	}

	sf::Color get_SHupgradeboxt()
	{
		if (rocket.get_SHUPNUM() == 0)
		{
			sf::Color color(150, 219, 137);
			return color;
		}
		else if (rocket.get_SHUPNUM() == 1)
		{
			sf::Color color(150, 219, 139);
			return color;
		}
		else
		{
			sf::Color color(150, 219, 140);
			return color;
		}
	}

private:
public:
private:
	Rocket rocket;
};
