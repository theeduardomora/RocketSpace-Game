/*#include "Collider.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>

//#pragma once

class Enemy
{

public:
	Enemy(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position)
	{
		body.setTexture(&texture);
		body.setSize(size);
		body.setPosition(position);
		//body.setPosition(sf::Vector2f(position.x * 2, position.y * 2));
		body.setOrigin(body.getSize() / 2.0f);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(body);
	}

	Collider& GetCollider()
	{
		ObstacleCollider = Collider(body);
		return ObstacleCollider;
	}

	void attack(int randnum)
	{

		if (randnum == 1)
		{
			light_attack_textures.push_back()
		}
		else if (randnum == 2)
		{
		}
		else if (randnum == 3)
		{
		}
		else if (randnum == 4)
		{
		}
	}

private:
public:
	sf::RectangleShape body;
	vector<sf::RectangleShape> light_attacks;
	vector<sf::Texture> light_attack_textures;
	vector<sf::RectangleShape> heavy_attacks;
	vector<sf::Texture> heavy_attack_textures;

private:
	Collider ObstacleCollider;
};*/ 