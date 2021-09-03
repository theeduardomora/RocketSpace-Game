
#include "Rocket.h"
#include <SFML/Graphics.hpp>
#include <vector>

#pragma once

class Enemy
{

public:

	Enemy() {

	}

	void Create_Enemy(sf::Texture texture, sf::Vector2f size, int enemy_num, int WINDOW_WIDTH,
		int WINDOW_HEIGHT)
	{
		sf::Vector2f position((WINDOW_WIDTH / 100) * 47, (WINDOW_HEIGHT / 100) * 10);

		this->thetexture = texture;
		body.setTexture(&thetexture, true);


		body.setSize(sf::Vector2f((float)body.getTextureRect().width, (float)body.getTextureRect().height));

		float temp1 = size.x / body.getSize().x;
		float temp2 = size.y / body.getSize().y;



		body.setScale(temp1, temp2);



		body.setPosition(position);
		//body.setPosition(sf::Vector2f(position.x * 2, position.y * 2));
		body.setOrigin(body.getSize() / 2.0f);
		this->enemy_num = enemy_num;

		if (enemy_num == 1)
		{
			//actual non-boss enemy
		}
		else if (enemy_num == 2)
		{

			this->health = 83.0f;
			//this->health = 12.0f;
			light_attack_textures.reserve(6);
			heavy_attack_textures.reserve(6);
			Texture temptext, temptext2, temptext3;

			temptext.loadFromFile("Sprites/tornado_1.png");
			this->attack_texture = temptext;

			this->light_attack_textures.push_back(attack_texture);

			temptext2.loadFromFile("Sprites/tornado_2.png");
			temptext3.loadFromFile("Sprites/Lightning_bolt_sheet.png");

			light_attack_textures.push_back(temptext2);
			heavy_attack_textures.push_back(temptext3);

			light_attacks.reserve(6);
			heavy_attacks.reserve(3);

			sf::RectangleShape bolt1, bolt2, bolt3, bolt4;


			this->torn1.setSize(sf::Vector2f(200.0f, 200.0f));
			torn2.setSize(sf::Vector2f(200.0f, 200.0f));
			torn3.setSize(sf::Vector2f(200.0f, 200.0f));
			torn4.setSize(sf::Vector2f(200.0f, 200.0f));
			torn5.setSize(sf::Vector2f(200.0f, 200.0f));
			torn6.setSize(sf::Vector2f(200.0f, 200.0f));


			torn1.setTexture(&light_attack_textures[0], true);
			torn2.setTexture(&light_attack_textures[0], true);
			torn3.setTexture(&light_attack_textures[0], true);
			torn4.setTexture(&light_attack_textures[0], true);
			torn5.setTexture(&light_attack_textures[0], true);
			torn6.setTexture(&light_attack_textures[0], true);



			float widthscale_torn = (WINDOW_WIDTH / 10) / light_attack_textures[0].getSize().x;
			float heightscale_torn = (WINDOW_HEIGHT / 10) / light_attack_textures[0].getSize().y;

			torn1.setScale(widthscale_torn, heightscale_torn);
			torn2.setScale(widthscale_torn, heightscale_torn);
			torn3.setScale(widthscale_torn, heightscale_torn);
			torn4.setScale(widthscale_torn, heightscale_torn);
			torn5.setScale(widthscale_torn, heightscale_torn);
			torn6.setScale(widthscale_torn, heightscale_torn);

			torn1.setPosition(body.getPosition());
			torn2.setPosition(body.getPosition());
			torn3.setPosition(body.getPosition());
			torn4.setPosition(body.getPosition());
			torn5.setPosition(body.getPosition());
			torn6.setPosition(body.getPosition());

			this->light_attacks.push_back(torn1);
			light_attacks.push_back(torn2);
			light_attacks.push_back(torn3);
			light_attacks.push_back(torn4);
			light_attacks.push_back(torn5);
			light_attacks.push_back(torn6);

			/*light_attacks[0] = torn1;
			light_attacks[1] = torn2;
			light_attacks[2] = torn3;
			light_attacks[3] = torn4;
			light_attacks[4] = torn5;
			light_attacks[5] = torn6;*/

			/*light_attacks[0].setTexture(&light_attack_textures[0], true);
			light_attacks[1].setTexture(&light_attack_textures[0], true);
			light_attacks[2].setTexture(&light_attack_textures[0], true);
			light_attacks[3].setTexture(&light_attack_textures[0], true);
			light_attacks[4].setTexture(&light_attack_textures[0], true);
			light_attacks[5].setTexture(&light_attack_textures[0], true);*/


			/*if(light_attacks.size() == 6) {
			attack_type_num += 1;
			attack_type_num -= 1;
		}*/


			/*bolt1.setTexture(&heavy_attack_textures[0], true);
			bolt2.setTexture(&heavy_attack_textures[0], true);
			bolt3.setTexture(&heavy_attack_textures[0], true);
			bolt4.setTexture(&heavy_attack_textures[0], true);

			float widthscale_bolt = (WINDOW_WIDTH / 8) / light_attack_textures[0].getSize().x;
			float heightscale_bolt = (WINDOW_HEIGHT / 2 * 1.5) / light_attack_textures[0].getSize().y;

			bolt1.setScale(widthscale_bolt, heightscale_bolt);
			bolt2.setScale(widthscale_bolt, heightscale_bolt);
			bolt3.setScale(widthscale_bolt, heightscale_bolt);
			bolt4.setScale(widthscale_bolt, heightscale_bolt);*/
		}
		else if (enemy_num == 3)
		{
		}
		else if (enemy_num == 4)
		{
		}
		else if (enemy_num == 5)
		{
		}

		attack_type_num = rand() % 2 + 1;
		//attack_type_num = 1;
		//attack_type_num = 2;

		one_unit_x = WINDOW_WIDTH / 100;
		one_unit_y = WINDOW_HEIGHT / 100;
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(body);
		/*for(int i =0; i < light_attacks_count; i++) {
			window.draw(light_attacks[i]);

			if(light_attacks.size() == 6) {
				attack_type_num++;
				attack_type_num--;
			}

		}*/ 

	}

	Collider& GetCollider()
	{
		ObstacleCollider = Collider(body);
		return ObstacleCollider;
	}

	bool boss_attack(bool attack_finished)
	{

		if(attack_finished) {
			attack_type_num = rand() % 2 + 1;
			//attack_type_num = 2;
			//attack_type_num = 1;
			attack_finished = false;
		}

		/*if (attack_type_num == 1) //side to side tornadoes
		{


				if (attack_counter == 0)
				{

					if(light_attacks[0].getPosition().x >= one_unit_x)
					{
						light_attacks[0].move(-(one_unit_x * 0.8), one_unit_y * 0.5);

					}
					else {
						light_attacks_count++;
						attack_counter++;
					}
				}

				else if (attack_counter == 1)
				{
					//light_attacks[1].setPosition(body.getPosition());
					if (light_attacks[1].getPosition().x >= one_unit_x)
					{
						light_attacks[0].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[1].move(-(one_unit_x * 0.8), one_unit_y * 0.5);
					}
					else {
						light_attacks_count++;
						attack_counter++;
					}
				}

				else if (attack_counter == 2)
				{
					//light_attacks[2].setPosition(body.getPosition());
					if (light_attacks[2].getPosition().x >= one_unit_x)
					{
						light_attacks[0].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[1].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[2].move(-(one_unit_x * 0.8), one_unit_y * 0.5);

					}
					else {
						light_attacks_count++;
						attack_counter++;
					}
				}
				else if (attack_counter == 3)
				{
					//light_attacks[3].setPosition(body.getPosition());
					if (light_attacks[3].getPosition().x >= one_unit_x)
					{
						light_attacks[0].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[1].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[2].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[3].move(-(one_unit_x * 0.8), one_unit_y * 0.5);
					}
					else {
						light_attacks_count++;
						attack_counter++;
					}
				}

				else if (attack_counter == 4)
				{
					//light_attacks[4].setPosition(body.getPosition());
					if (light_attacks[4].getPosition().x >= one_unit_x)
					{
						light_attacks[0].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[1].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[2].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[3].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[4].move(-(one_unit_x * 0.8), one_unit_y * 0.5);
					}
					else {
						light_attacks_count++;
						attack_counter++;
					}
				}
				else if (attack_counter == 5)
				{
					//light_attacks[5].setPosition(body.getPosition());
					if (light_attacks[5].getPosition().x >= one_unit_x)
					{
						light_attacks[0].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[1].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[2].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[3].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[4].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[5].move(-(one_unit_x * 0.8), one_unit_y * 0.5);
					}
					else {
						light_attacks_count++;
						attack_counter++;
					}
			}


			else {

					if( (light_attacks[5].getPosition().x < 98 * one_unit_x) && (light_attacks[5].getPosition().y > one_unit_y)) {
						light_attacks[0].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[1].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[2].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[3].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[4].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[5].move((one_unit_x * 1.6), one_unit_y * 0.5);
					}

					else if((light_attacks[5].getPosition().x > one_unit_x) && (light_attacks[5].getPosition().y > one_unit_y)) {
						light_attacks[0].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[1].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[2].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[3].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[4].move((one_unit_x * 1.6), one_unit_y * 0.5);
						light_attacks[5].move(-(one_unit_x * 1.6), one_unit_y * 0.5);
					}
					else {
						return true;
					}
			}

			return false;
		}*/

		if(attack_type_num == 1) {
			if(attack_counter == 0) {
			if(body.getPosition().x < 97 * one_unit_x || body.getPosition().y > 4 * one_unit_y) {
				if(body.getPosition().x < 97 * one_unit_x ) {
						body.move(sf::Vector2f(one_unit_x * 1.8, 0));
				}
				if(body.getPosition().y > 4 * one_unit_y) {
					body.move(sf::Vector2f(0, -(one_unit_y * 1.8)));
				}
			}
			else {
				body.setPosition(97 * one_unit_x, 4 * one_unit_y);
				attack_counter++;
			}
			}

			if(attack_counter == 1) {
			if(body.getPosition().x > 3 * one_unit_x || body.getPosition().y < 29 * one_unit_y) {
					if(body.getPosition().x > 3 * one_unit_x) {
						body.move(sf::Vector2f(-(one_unit_x * 2.2), 0));
				}
				if(body.getPosition().y < 29 * one_unit_y) {
					body.move(sf::Vector2f(0, (one_unit_y * 1.6)));
				}
			}
			else {
				body.setPosition(3 * one_unit_x, 29 * one_unit_y);
				attack_counter++;
			}
			}

			if(attack_counter == 2) {
			if(body.getPosition().x < 97 * one_unit_x  || body.getPosition().y < 54 * one_unit_y) {
					if(body.getPosition().x < 97 * one_unit_x ) {
						body.move(sf::Vector2f(one_unit_x * 2.2, 0));
				}
				if(body.getPosition().y < 54 * one_unit_y) {
					body.move(sf::Vector2f(0, (one_unit_y * 1.6)));
				}
			}
			else {
				body.setPosition(97 * one_unit_x, 54 * one_unit_y);
				attack_counter++;
			}
			}

			if(attack_counter == 3) {
			if(body.getPosition().x > 3 * one_unit_x || body.getPosition().y <  79 * one_unit_y) {
					if(body.getPosition().x > 3 * one_unit_x) {
						body.move(sf::Vector2f(-(one_unit_x * 2.2), 0));
				}
				if(body.getPosition().y < 79 * one_unit_y) {
					body.move(sf::Vector2f(0, (one_unit_y * 1.6)));
				}
			}
			else {
				body.setPosition(3 * one_unit_x, 79 * one_unit_y);
				attack_counter++;
			}
		}


		if(attack_counter == 4) {
			if(body.getPosition().x < 97 * one_unit_x  || body.getPosition().y < 96 * one_unit_y) {
					if(body.getPosition().x < 97 * one_unit_x ) {
						body.move(sf::Vector2f(one_unit_x * 2.2, 0));
				}
				if(body.getPosition().y < 96 * one_unit_y) {
					body.move(sf::Vector2f(0, (one_unit_y * 1.6)));
				}
			}
			else {
				body.setPosition(97 * one_unit_x, 96 * one_unit_y);
				attack_counter++;
			}
		}

		if(attack_counter == 5) {
			if(body.getPosition().y > 3 * one_unit_y) {
				body.move(sf::Vector2f(0, (-one_unit_y * 2.4)));
			}
			else {
				body.setPosition(body.getPosition().x, 3 * one_unit_y);
				attack_counter++;
			}

		}

		if(attack_counter == 6) {
			if(body.getPosition().x > 45 * one_unit_x) {
				body.move(sf::Vector2f((-one_unit_x * 2.4), 0));
			}
			else {
				body.setPosition(45 * one_unit_x, body.getPosition().y);
				attack_counter++;
			}
		}

		if(attack_counter == 7) {
			attack_counter = 0;
			return true;
		}

			return false;
		}


		if (attack_type_num == 2) //moves around screen
		{
			if(attack_counter == 0) {
			if(body.getPosition().x > 3 * one_unit_x || body.getPosition().y < 97 * one_unit_y) {
				if(body.getPosition().x > 3 * one_unit_x ) {
						body.move(sf::Vector2f(-one_unit_x * 1.8, 0));
				}
				if(body.getPosition().y < 98 * one_unit_y) {
					body.move(sf::Vector2f(0, one_unit_y * 2.2));
				}
			}
			else {
				body.setPosition(3* one_unit_x, 97 * one_unit_y);
				attack_counter++;
			}
			}

			if(attack_counter == 1) {
			if(body.getPosition().x < 97 * one_unit_x || body.getPosition().y < 90 * one_unit_y) {
					if(body.getPosition().x < 97 * one_unit_x ) {
						body.move(sf::Vector2f(one_unit_x * 2.0, 0));
				}
				if(body.getPosition().y < 90 * one_unit_y) {
					body.move(sf::Vector2f(0, -(one_unit_y * 0.8)));
				}
			}
			else {
				body.setPosition(97 * one_unit_x, 90 * one_unit_y);
				attack_counter++;
			}
			}

			if(attack_counter == 2) {
			if(body.getPosition().x > 3 * one_unit_x  || body.getPosition().y > 3 * one_unit_y) {
					if(body.getPosition().x > 3 * one_unit_x ) {
						body.move(sf::Vector2f(-one_unit_x * 2.2, 0));
				}
				if(body.getPosition().y > 3 * one_unit_y) {
					body.move(sf::Vector2f(0, -(one_unit_y * 2.2)));
				}
			}
			else {
				body.setPosition(3 * one_unit_x, 3 * one_unit_y);
				attack_counter++;
			}
			}

			if(attack_counter == 3) {
			if(body.getPosition().x < 45 * one_unit_x || body.getPosition().y > 3 * one_unit_y) {
					if(body.getPosition().x < 45 * one_unit_x) {
						body.move(sf::Vector2f(one_unit_x * 1.8, 0));
				}
				if(body.getPosition().y > 3 * one_unit_y) {
					body.move(sf::Vector2f(0, -(one_unit_y * 1.6)));
				}
			}
			else {
				body.setPosition(45 * one_unit_x, 3 * one_unit_y);
				attack_counter++;
			}
		}
			if(attack_counter == 4) {
				attack_counter = 0;
				return true;
			}

	}
		return false;
	}

private:
public:
	sf::RectangleShape body;
	std::vector<sf::RectangleShape> heavy_attacks;
	int light_attacks_count = 1;
	sf::RectangleShape torn1, torn2, torn3, torn4, torn5, torn6;
	float health = 1.0f;
	int attack_type_num = 0;
	int enemy_num = 0;

private:
	Collider ObstacleCollider;
	std::vector<sf::RectangleShape> light_attacks;
	std::vector<sf::Texture> light_attack_textures;
	std::vector<sf::Texture> heavy_attack_textures;
	Texture thetexture ;
	Texture attack_texture;

	int attack_counter = 0;
	float one_unit_x;
	float one_unit_y;

};