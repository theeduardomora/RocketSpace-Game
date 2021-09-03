#include <SFML/Graphics.hpp>


#pragma once
class PBAnimation
{
public:
	PBAnimation(sf::Texture* texture, sf::Vector2u imageCount, int WINDOW_WIDTH, int WINDOW_HEIGHT)
	{
		this->ImageCount = imageCount;
		CurrentImage.x = 0;

		uvRect.width = texture->getSize().x / (float)ImageCount.x;
		//uvRect.width = 40;
		uvRect.height = texture->getSize().y / (float)ImageCount.y;

		uvRect.top = 0;
		uvRect.left = 0;

		Curr_Sprite_num = 0;
		body.setTexture(texture);

		body.setSize(sf::Vector2f(uvRect.width, uvRect.height));
		body.setPosition(sf::Vector2f((WINDOW_WIDTH / 2) * 1.4, 1.51 * WINDOW_HEIGHT / 2)); //placed next to rocket
		body.setTextureRect(uvRect);
	}

	void Update()
	{
		//Curr_Sprite_num++;
		if (Curr_Sprite_num % 10 == 0)
		{
			Curr_Sprite_num = 0;
			uvRect.left = 0;
		}
		else
		{
			uvRect.left = Curr_Sprite_num * uvRect.width;
		}
		this->body.setTextureRect(uvRect);
		Curr_Sprite_num++;
	}

	const sf::Vector2f GetPosition()
	{
		return body.getPosition();
	}

	const sf::Vector2f GetSize()
	{
		return body.getSize();
	}
	const sf::RectangleShape GetBody()
	{
		return body;
	}

	float ReturnRocketSpeed()
	{
		switch (Curr_Sprite_num)
		{
			case 0:
				return 0.7;
				break;
			case 1:
				return 0.75;
				break;
			case 2:
				return 0.75;
				break;
			case 3:
				return 0.8;
				break;
			case 4:
				return 0.8;
				break;
			case 5:
				return 0.8;
				break;
			case 6:
				return 0.85;
				break;
			case 7:
				return 0.9;
				break;
			case 8:
				return 0.95;
				break;
			case 9:
				return 1.0;
				break;
			default:
				return 1.0;
				break;
		}
	}

private:
public:
	sf::IntRect uvRect;

private:
	sf::Vector2u ImageCount;
	sf::Vector2u CurrentImage;
	sf::RectangleShape body;
	int Curr_Sprite_num;
};
