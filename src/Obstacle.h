#include "Collider.h"
#include <SFML/Graphics.hpp>


#pragma once

class Obstacle
{

public:
	Obstacle(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position)
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

private:
public:
sf::RectangleShape body;
private:
Collider ObstacleCollider;

};
