
#include <SFML/Graphics.hpp>


#pragma once
class Collider
{

public:
	Collider(sf::RectangleShape& body) :
		body(body)
	{
	}

	Collider() {

	}

	bool CheckCollision(Collider& other, float push, unsigned int& WINDOW_WIDTH, unsigned int& WINDOW_HEIGHT)
	{
		sf::Vector2f otherPosition = other.GetPosition();
		sf::Vector2f otherHalfSize = other.GetHalfSize();
		sf::Vector2f thisPosition = GetPosition();
		sf::Vector2f thisHalfSize = GetHalfSize();

		
		float deltaX = otherPosition.x - thisPosition.x;
		float deltaY = otherPosition.y - thisPosition.y;

		/*if(abs(deltaX) > WINDOW_WIDTH / 8) {
			return false;
		}
		if(abs(deltaY) > WINDOW_HEIGHT / 6) {
			return false;
		}*/


		float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
		float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

		float coll_width =  (((float)WINDOW_WIDTH / 10) * .1);
		float coll_height =  (((float)WINDOW_HEIGHT / 12) * .1);
		//coll_width++;
		//coll_height++;



		if ( (intersectX <= (-coll_width) ) && (intersectY <= (-coll_height) ) )
		{
			push = std::min(std::min(push, 0.0f), 1.0f);

			if (intersectX > intersectY)
			{

				if (deltaX > 0.0f)
				{
					Move(intersectX * (1.0f - push), 0.0f);
					other.Move(-intersectX * push, 0.0f);
				}
				else
				{
					Move(-intersectX * (1.0f - push), 0.0f);
					other.Move(intersectX * push, 0.0f);
				}
			}

			else
			{

				if (deltaY > 0.0f)
				{
					Move(0.0f, intersectY * (1.0f - push));
					other.Move(0.0f, -intersectY * push);
				}

				else
				{
					Move(0.0f, -intersectY * (1.0f - push));
					other.Move(0.0f, intersectY * push);
				}
			}

			return true;
		}

		return false;
	}

	void Move(float dx, float dy)
	{
		body.move(dx, dy);
	}

	sf::Vector2f GetPosition()
	{
		return body.getPosition();
	}
	sf::Vector2f GetHalfSize()
	{
		return body.getSize() / 2.0f;
	}

private:
public:
private:
	sf::RectangleShape body;
};