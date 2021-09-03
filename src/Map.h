#include "Game.h"
#include <SFML/Graphics.hpp>


#pragma once
class Map
{

public:
	Map(int level, int WINDOW_WIDTH, int WINDOW_HEIGHT) :
		level(level),
		unit_width(WINDOW_WIDTH / 100),
		unit_height(WINDOW_HEIGHT / 100)
	{

		switch (level)
		{
			case 1:
				Screen_background.loadFromFile("Sprites/CloudsInSky_3.png");
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
		}

		same_bg_count = 1;
		bg_num = 1;
	}

	void populate_screen()
	{
	}

	void change_screen()
	{
		std::string background_name;

		switch (level)
		{

			case 1:
				same_bg_count++;
				if (same_bg_count == 3)
				{

					background_name = "CloudsInSky_" + std::to_string(bg_num) + ".png";
					Screen_background.loadFromFile(background_name);
					same_bg_count = 0;
					bg_num++;
				}

				break;

			case 2:

				same_bg_count++;
				if (same_bg_count == 3)
				{

					background_name = "HighSky_" + std::to_string(bg_num) + ".png";
					Screen_background.loadFromFile(background_name);
					same_bg_count = 0;
					bg_num++;
				}

				break;

			case 3:

				same_bg_count++;
				if (same_bg_count == 3)
				{

					background_name = "HighSky_" + std::to_string(bg_num) + ".png";
					Screen_background.loadFromFile(background_name);
					same_bg_count = 0;
					bg_num++;
				}

				break;

			case 4:

				same_bg_count++;
				if (same_bg_count == 3)
				{

					background_name = "HighSky_" + std::to_string(bg_num) + ".png";
					Screen_background.loadFromFile(background_name);
					same_bg_count = 0;
					bg_num++;
				}

				break;

			default:
				break;
		}

	} //end of change_screen

private:
public:
	sf::Texture Screen_background;

private:
	int level;
	float unit_width;
	float unit_height;
	int same_bg_count;
	int bg_num;
};
