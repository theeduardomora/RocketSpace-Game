#include <SFML/Graphics.hpp>
#include "Collider.h"
#include <iostream> 
#pragma once


using namespace sf;



class Rocket
{

public:
	Rocket();
	Rocket(int num_type, unsigned int WINDOW_HEIGHT, unsigned int WINDOW_WIDTH, sf::Texture& texture)
	{
		
		//clock.restart(); 
		elapsedtime = clock.getElapsedTime().asSeconds();
		elapsedtimeRatio = 1 / (8.0f / elapsedtime);

		this->num_type = num_type;
		//was 0.25
		fuel_constant = .1375;
		this->WINDOW_HEIGHT = WINDOW_HEIGHT;
		this->WINDOW_WIDTH = WINDOW_WIDTH;
		if (num_type == 1)
		{
			speed_y = WINDOW_HEIGHT / 1.6;
			speed_x = WINDOW_WIDTH / 1.8;
		}

		/*Clock clock; 
		clock.getElapsedTime(); */ 



		curr_speed_x = speed_x;
		curr_speed_y = speed_y;
		body.setTexture(&texture, true);


		Proj_texture.loadFromFile("Sprites/Projectile.png");


		float proj_scale_x = (float)(WINDOW_WIDTH / 20) / Proj_texture.getSize().x;
		float proj_scale_y = (float)(WINDOW_HEIGHT / 14) / Proj_texture.getSize().y;


		proj1.setTexture(&Proj_texture, true);
		proj2.setTexture(&Proj_texture, true);
		proj3.setTexture(&Proj_texture, true);
		proj4.setTexture(&Proj_texture, true);
		proj1.setSize((Vector2f)Proj_texture.getSize());
		proj2.setSize((Vector2f)Proj_texture.getSize());
		proj3.setSize((Vector2f)Proj_texture.getSize());
		proj4.setSize((Vector2f)Proj_texture.getSize());

		//proj1.setFillColor(Color::Red);
		//proj2.setFillColor(Color::Red);




		proj1.setScale(proj_scale_x, proj_scale_y);
		proj2.setScale(proj_scale_x, proj_scale_y);
		proj3.setScale(proj_scale_x, proj_scale_y);
		proj4.setScale(proj_scale_x, proj_scale_y);


		proj1.setOrigin(proj1.getSize() / 2.0f);
		proj2.setOrigin(proj1.getSize() / 2.0f);
		proj3.setOrigin(proj1.getSize() / 2.0f);
		proj4.setOrigin(proj1.getSize() / 2.0f);

		/*proj1.setPosition(0,10);
		proj2.setPosition(0,11);
		proj3.setPosition(0,12);
		proj4.setPosition(0,13);*/


	}

	void setLaunchSpeed(float speedfact)
	{
		this->curr_speed_x = speed_x * speedfact;
		this->curr_speed_y = speed_y * speedfact;
	}

	void setNetSpeed(float speedfact)
	{
		this->speed_x = speed_x * speedfact;
		this->speed_y = speed_y * speedfact;
	}

	void Control_Rocket(bool boss_time) {
		//clock.restart();
		//std::cout << clock.getElapsedTime().asSeconds() << '\n';
		sf::Vector2f movement(0.0f, 0.0f);


			/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if(!PlayerRocket.proj_thrown1) {
					PlayerRocket.proj1.setPosition(body.getPosition());
					PlayerRocket.proj_thrown1 = true;
				}
				else if(!PlayerRocket.proj_thrown2) {
					PlayerRocket.proj2.setPosition(body.getPosition());
					PlayerRocket.proj_thrown2 = true;
				}

			}

			if(PlayerRocket.proj_thrown1) {
			PlayerRocket.proj1.move(0, WINDOW_HEIGHT * 0.05);
			if(PlayerRocket.proj1.getPosition().y < 0) {
				PlayerRocket.proj_thrown1 = false;
			}
			}



			if(PlayerRocket.proj_thrown2) {
			PlayerRocket.proj2.move(0, WINDOW_HEIGHT * 0.05);
			if(PlayerRocket.proj2.getPosition().y < 0) {
				PlayerRocket.proj_thrown2 = false;
			}
			}*/
			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (body.getPosition().y >= 0 || (!boss_time) ) ) {
				movement.y -= curr_speed_y * 0.02;
			}

			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (body.getPosition().x < (float)WINDOW_WIDTH * 0.97)) {
					movement.x += curr_speed_x * 0.02;
			}

			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (body.getPosition().y < (float)WINDOW_HEIGHT * 0.97)) {
					movement.y += curr_speed_y * 0.02;
			}

			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (body.getPosition().x > 0)) {
					movement.x -= curr_speed_x * 0.02;
			}

			/**/


			if(!boss_time) {
			fuel -= fuel_constant; //fuel constant
			}

			this->body.move(movement);
			//clock.restart();
			sf::sleep(seconds(0.02));

	}

	void move_projectile() {


		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if(!proj_thrown1) {
					proj1.setPosition(body.getPosition());
					proj_thrown1 = true;
				}
				else if((!proj_thrown2) && (shootTimer >= 3)) {
					proj2.setPosition(body.getPosition());
					proj_thrown2 = true;
				}
				//move_projectile();
			}


		if(proj_thrown1) {
			shootTimer++;
			proj1.move(sf::Vector2f(0, -32.0f));
			if(proj1.getPosition().y < 0) {
				proj_thrown1 = false;
				proj1.setPosition(0,-10.0f);

			}
			}

			if(proj_thrown2) {
			proj2.move(sf::Vector2f(0, -32.0f));
			if(proj2.getPosition().y < 0) {
				proj_thrown2 = false;
				proj2.setPosition(0,-10.0f);
				shootTimer = 0;
			}
			}

			//sf::sleep(seconds(0.02));


	}
	void upgrade_rocket() {
		this->num_type++;
		speed_y = (num_type - 1) * 1.5 * (WINDOW_HEIGHT / 1.6) ;
		speed_x = (num_type - 1) * 1.5 * (WINDOW_WIDTH / 1.8) ;

		this->rocket_damage = 1.75 * (num_type - 1);

		this->fuel_constant = 0.25 * 0.75 * (num_type - 1);

	}

	void FT_upgrade() {
		this->FT_UP_NUM++;
		if(FT_UP_NUM == 1) {
			fuel_constant /= 1.4;
		}
		else if(FT_UP_NUM == 2) {
			fuel_constant /= 1.4;
		}
		else if(FT_UP_NUM == 3) {
			fuel_constant /= 1.4;
		}


	}

	void BR_upgrade() {
		this->BR_UP_NUM++;
		if(BR_UP_NUM == 1) {
			this->setNetSpeed(1.2);
		}
		else if(BR_UP_NUM == 2) {
			this->setNetSpeed(1.15);
		}
		else if(BR_UP_NUM == 3) {
			this->setNetSpeed(1.1);
		}
	}

	void SH_upgrade() {
		this->SH_UP_NUM++;
		if(SH_UP_NUM == 1) {
			rocket_damage *= 1.3;
		}
		else if(SH_UP_NUM == 2) {
			rocket_damage *= 1.3;
		}
		else if(SH_UP_NUM == 3) {
			rocket_damage *= 1.25;
		}

	}

	int get_coinscollected() {
		return coins_coll;
	}

	int get_fuelcollected() {
		return fuel_coll;
	}

	int get_score() {
		return score;
	}

	void increase_coinscollected() {
		coins_coll += 10;
	}


	void increase_fuelcollected() {
		fuel_coll += 10;
	}

	void increase_score() {
		score += 10;
	}


	int get_FTUPNUM() {
		return FT_UP_NUM;
	}

	int get_BRUPNUM() {
		return BR_UP_NUM;
	}

	int get_SHUPNUM() {
		return SH_UP_NUM;
	}

	double get_fuelconstant() {
		return fuel_constant;
	}




	Collider& GetCollider() {
		ObstacleCollider1 = Collider(body);
		return ObstacleCollider1;
	}

	Collider& GetColliderProj1() {
		ObstacleCollider2 = Collider(proj1);
		return ObstacleCollider2;
	}

	Collider& GetColliderProj2() {
		ObstacleCollider3 = Collider(proj2);
		return ObstacleCollider3;
	}

	/*Collider& GetColliderProj3() {
		ObstacleCollider = Collider(proj3);
		return ObstacleCollider;
	}

	Collider& GetColliderProj4() {
		ObstacleCollider = Collider(proj4);
		return ObstacleCollider;
	}*/

private:
public:
	sf::RectangleShape body;
	int health = 2;
	float fuel = 100;
	int coins_coll = 0;
	int fuel_coll = 0;
	Texture Proj_texture;
	bool proj_thrown1 = false;
	bool proj_thrown2 = false;
	sf::RectangleShape proj1, proj2, proj3, proj4;
	unsigned int WINDOW_HEIGHT;
	unsigned int WINDOW_WIDTH;
	double rocket_damage = 1;
	int num_type;


private:
	int FT_UP_NUM = 0;
	int BR_UP_NUM = 0;
	int MG_UP_NUM = 0;
	int SH_UP_NUM = 0;
	float speed_x;
	float speed_y;
	float curr_speed_x;
	float curr_speed_y;
	int score = 0;
	Collider ObstacleCollider1, ObstacleCollider2, ObstacleCollider3;
	int shootTimer  = 0;
	double fuel_constant;
	Clock clock;
	double elapsedtime; 
	float elapsedtimeRatio; 

	
};
