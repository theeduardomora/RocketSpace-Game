#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "PBAnimation.h"
#include "Rocket.h"
#include "ShopMenu.h"
#include "Obstacle.h"
#include "Collider.h"
#include "Enemy.h"
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <string>



using namespace sf;


std::pair <std::vector<std::vector<Obstacle>>, std::vector<sf::Texture>> Change_Screen(Sprite& gamebackground, Game& game, float WINDOW_WIDTH, float WINDOW_HEIGHT);
void hurt_animation(Rocket& PlayerRocket, float& width_scale, float& height_scale, bool hurt);
void create_boss(Enemy& boss, int boss_num, int WINDOW_WIDTH, int WINDOW_HEIGHT);
void draw_boss(Enemy& boss, RenderWindow& window, int boss_num, bool intro);
void new_rocket(sf::RenderWindow& window, int WINDOW_WIDTH, int WINDOW_HEIGHT);

Texture temptexture;

void boss_animation(sf::Sprite& BossSprite, int boss_num, int WINDOW_WIDTH, int WINDOW_HEIGHT);
float small_unit_width, small_unit_height = 0.0f;

int main()
{
	bool boss1_defeated = false;

	sf::Music music;
		if (!music.openFromFile("Sounds/rocketspace_background_music.wav"))
			return -1; // error

	music.setVolume(65.0f);

	auto fullscreen = sf::VideoMode::getFullscreenModes();
	Texture Rockett, backgroundt, startbuttont, loadbuttont, aboutbuttont, gamebackgroundt;
	Texture DialogBoxt;
	RenderWindow window(fullscreen[0], "Rocket Space");
	Event event;

	window.setFramerateLimit(60);
	sf::Clock clock;


	Rockett.loadFromFile("Sprites/Rocket.png");
	backgroundt.loadFromFile("Sprites/RSTitleScreenFS.png");
	startbuttont.loadFromFile("Sprites/start_button.png");
	loadbuttont.loadFromFile("Sprites/load_button.png");
	gamebackgroundt.loadFromFile("Sprites/GroundandSky.png");
	DialogBoxt.loadFromFile("Sprites/DialogBox_long.png");
	auto WINDOW_HEIGHT = fullscreen[0].height;
	auto WINDOW_WIDTH = fullscreen[0].width;
	//sf::Time t1 = seconds(0.3);
	int alt_count = 0;

	bool boss_time = false;

	Enemy Boss;
	int boss_num = 0;
	bool attack_finished = false;

	Rocket PlayerRocket(1, WINDOW_HEIGHT, WINDOW_WIDTH, Rockett);
	//Sprite RocketSprite(Rockett);
	//PlayerRocket.body.setTexture(&Rockett, true);
	Sprite background(backgroundt), startbutton(startbuttont), loadbutton(loadbuttont), gamebackground(gamebackgroundt);
	Sprite DialogBox(DialogBoxt);
	DialogBox.setPosition(sf::Vector2f(0,0));

	startbutton.setPosition(sf::Vector2f((WINDOW_WIDTH / 4), WINDOW_HEIGHT / 2));
	loadbutton.setPosition(sf::Vector2f((WINDOW_WIDTH / 2), WINDOW_HEIGHT / 2));

	//view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	/*std::cout << backgroundt.getSize().y << "\n";
	std::cout << backgroundt.getSize().x << "\n";*/


	//sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT) );


	float heightscale_ts = (float)WINDOW_HEIGHT / backgroundt.getSize().y;
	float widthscale_ts = (float)WINDOW_WIDTH / backgroundt.getSize().x;

	float heightscale_sb = (float)(WINDOW_HEIGHT / 8) / startbuttont.getSize().y;
	float widthscale_sb = (float)(WINDOW_WIDTH / 6) / startbuttont.getSize().x;

	float heightscale_lb = (float)(WINDOW_HEIGHT / 8) / loadbuttont.getSize().y;
	float widthscale_lb = (float)(WINDOW_WIDTH / 6) / loadbuttont.getSize().x;

	float heightscale_R = (float)(WINDOW_HEIGHT / 7) / Rockett.getSize().y;
	float widthscale_R = (float)(WINDOW_WIDTH / 14) / Rockett.getSize().x;

	float heightscale_gb = (float)WINDOW_HEIGHT / gamebackgroundt.getSize().y;
	float widthscale_gb = (float)WINDOW_WIDTH / gamebackgroundt.getSize().x;


	float heightscale_db = (float)(WINDOW_HEIGHT / 4) / DialogBoxt.getSize().y;
	float widthscale_db = (float)WINDOW_WIDTH / DialogBoxt.getSize().x;

	bool display_up = true;


	background.setScale(widthscale_ts, heightscale_ts);
	startbutton.setScale(widthscale_sb, heightscale_sb);
	loadbutton.setScale(widthscale_lb, heightscale_lb);
	gamebackground.setScale(widthscale_gb, heightscale_gb);

	PlayerRocket.body.setSize(sf::Vector2f((float)Rockett.getSize().x, (float)Rockett.getSize().y));
	PlayerRocket.body.setScale(widthscale_R, heightscale_R);

	PlayerRocket.body.setOrigin(PlayerRocket.body.getSize().x / 2, PlayerRocket.body.getSize().y / 2 );

	DialogBox.setScale(widthscale_db, heightscale_db);


	bool at_titlescreen = true;
	bool in_game = false;
	bool loadgame_screen = false;

	bool starting_newgame = true;
	bool damage_state = false;

	Game game(0);

	Text coincount, fueltankcount, FT_text, BR_text, SH_text, PURCHASE;
	Font font;
	font.loadFromFile("Fonts/Pixeboy-z8XGD.ttf");

	coincount.setFont(font);
	fueltankcount.setFont(font);
	//score.setFont(font);
	FT_text.setFont(font);
	BR_text.setFont(font);
	SH_text.setFont(font);
	PURCHASE.setFont(font);

	coincount.setCharacterSize( ((float)(WINDOW_HEIGHT / 100) * 2));
	fueltankcount.setCharacterSize( ((float)(WINDOW_HEIGHT / 100) * 2));
	//score.setCharacterSize( ((float)(WINDOW_HEIGHT / 100) * 5));
	FT_text.setCharacterSize( ((float)(WINDOW_WIDTH / 100) * 1.5));
	BR_text.setCharacterSize( ((float)(WINDOW_WIDTH / 100) * 1.5));
	SH_text.setCharacterSize( ((float)(WINDOW_WIDTH / 100) * 1.5));
	PURCHASE.setCharacterSize( ((float)(WINDOW_WIDTH / 100) * 1.5));


	coincount.setFillColor(Color::White);
	fueltankcount.setFillColor(Color::White);
	//score.setFillColor(Color::White);
	FT_text.setFillColor(Color::Black);
	BR_text.setFillColor(Color::Black);
	SH_text.setFillColor(Color::Black);
	PURCHASE.setFillColor(Color::Black);



	coincount.setPosition((float)(WINDOW_WIDTH / 100) * 78, ((float)(WINDOW_HEIGHT / 100) * 3 ));
	fueltankcount.setPosition((float)(WINDOW_WIDTH / 100) * 93, ((float)(WINDOW_HEIGHT / 100) * 3 ));
	//score.setPosition((float)(WINDOW_WIDTH / 100) * 91, ((float)(WINDOW_HEIGHT / 100) * 1 ));
	FT_text.setPosition((float)(WINDOW_WIDTH / 100) * 63, ((float)(WINDOW_HEIGHT / 100) * 40 )  );
	BR_text.setPosition((float)(WINDOW_WIDTH / 100) * 63, ((float)(WINDOW_HEIGHT / 100) * 40 )  );
	SH_text.setPosition((float)(WINDOW_WIDTH / 100) * 63, ((float)(WINDOW_HEIGHT / 100) * 40 )  );
	PURCHASE.setPosition((float)(WINDOW_WIDTH / 100) * 63, ((float)(WINDOW_HEIGHT / 100) * 60 ));
	FT_text.setLineSpacing(1.3);
	BR_text.setLineSpacing(1.3);
	SH_text.setLineSpacing(1.3);


	//ShopMenu shopmenuobj(PlayerRocket);

	PURCHASE.setString("Purchase?");
	/*FT_square.setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3 * 1.1);
	BR_square.setPosition(WINDOW_WIDTH / 3, (((WINDOW_HEIGHT / 3) * 1.1) + WINDOW_HEIGHT / 20 * 2));
	SH_square.setPosition(WINDOW_WIDTH / 3, (((WINDOW_HEIGHT / 3) * 1.1) + WINDOW_HEIGHT / 20 * 4));*/


	Texture shop_menut, next_buttont;
	next_buttont.loadFromFile("Sprites/Next_button.png");
	shop_menut.loadFromFile("Sprites/Shop_Menu.png");
	Sprite shop_menu(shop_menut), next_button(next_buttont);

	shop_menu.setPosition((WINDOW_WIDTH / 4), (WINDOW_HEIGHT / 4));

	next_button.setPosition((WINDOW_WIDTH / 2) * 1.35, (WINDOW_HEIGHT / 2) * 1.45);



	float heightscale_sm = ((float)WINDOW_HEIGHT / 2) / shop_menut.getSize().y;
	float widthscale_sm = ((float) WINDOW_WIDTH/ 2) / shop_menut.getSize().x;

	float heightscale_nb = ((float)WINDOW_HEIGHT / 13) / next_buttont.getSize().y;
	float widthscale_nb = ((float) WINDOW_WIDTH/ 11) / next_buttont.getSize().x;

	shop_menu.setScale(widthscale_sm, heightscale_sm);
	next_button.setScale(widthscale_nb, heightscale_nb);



	//FT_square.setScale(widthscale_sm, heightscale_sm);
	//BR_square.setScale(widthscale_sm, heightscale_sm);
	//SH_square.setScale(widthscale_sm, heightscale_sm);

	auto shop_menu_bounds = shop_menu.getLocalBounds();


	sf::RectangleShape FT_square( sf::Vector2f(shop_menu_bounds.height / 10, shop_menu_bounds.height / 10));
	sf::RectangleShape FT_square2( sf::Vector2f(shop_menu_bounds.height / 10, shop_menu_bounds.height / 10));
	sf::RectangleShape FT_square3( sf::Vector2f(shop_menu_bounds.height / 10, shop_menu_bounds.height / 10));
	sf::RectangleShape BR_square( sf::Vector2f(shop_menu_bounds.height / 10, shop_menu_bounds.height / 10));
	sf::RectangleShape BR_square2( sf::Vector2f(shop_menu_bounds.height / 10, shop_menu_bounds.height / 10));
	sf::RectangleShape BR_square3( sf::Vector2f(shop_menu_bounds.height / 10, shop_menu_bounds.height / 10));
	sf::RectangleShape SH_square( sf::Vector2f(shop_menu_bounds.height / 10, shop_menu_bounds.height / 10));
	sf::RectangleShape SH_square2( sf::Vector2f(shop_menu_bounds.height / 10, shop_menu_bounds.height / 10));
	sf::RectangleShape SH_square3( sf::Vector2f(shop_menu_bounds.height / 10, shop_menu_bounds.height / 10));

	auto upgrade_squares_bounds = FT_square.getLocalBounds();

	FT_square.setPosition((WINDOW_WIDTH / 4) + ((shop_menu_bounds.width / 3) * widthscale_sm), (WINDOW_HEIGHT / 4) + ((shop_menu_bounds.height / 4) * heightscale_sm));

	BR_square.setPosition((WINDOW_WIDTH / 4) + ((shop_menu_bounds.width / 3) * widthscale_sm), (WINDOW_HEIGHT / 4) + ((shop_menu_bounds.height / 4) * heightscale_sm) + (2.5 * upgrade_squares_bounds.height * heightscale_sm ));

	SH_square.setPosition((WINDOW_WIDTH / 4) + ((shop_menu_bounds.width / 3) * widthscale_sm), (WINDOW_HEIGHT / 4) + ((shop_menu_bounds.height / 4) * heightscale_sm) + (5 * upgrade_squares_bounds.height * heightscale_sm));


	FT_square.setScale(widthscale_sm, heightscale_sm);

	FT_square2.setPosition((WINDOW_WIDTH / 4) + ((shop_menu_bounds.width / 3) * widthscale_sm) + (2*FT_square.getGlobalBounds().width) , (WINDOW_HEIGHT / 4) + ((shop_menu_bounds.height / 4) * heightscale_sm));
	FT_square3.setPosition((WINDOW_WIDTH / 4) + ((shop_menu_bounds.width / 3) * widthscale_sm) + (4*FT_square.getGlobalBounds().width) , (WINDOW_HEIGHT / 4) + ((shop_menu_bounds.height / 4) * heightscale_sm));
	FT_square2.setScale(widthscale_sm, heightscale_sm);
	FT_square3.setScale(widthscale_sm, heightscale_sm);

	BR_square.setScale(widthscale_sm, heightscale_sm);

	BR_square2.setPosition((WINDOW_WIDTH / 4) + ((shop_menu_bounds.width / 3) * widthscale_sm)  + (2*FT_square.getGlobalBounds().width), (WINDOW_HEIGHT / 4) + ((shop_menu_bounds.height / 4) * heightscale_sm) + (2.5 * upgrade_squares_bounds.height * heightscale_sm ));
	BR_square3.setPosition((WINDOW_WIDTH / 4) + ((shop_menu_bounds.width / 3) * widthscale_sm)  + (4*FT_square.getGlobalBounds().width), (WINDOW_HEIGHT / 4) + ((shop_menu_bounds.height / 4) * heightscale_sm) + (2.5 * upgrade_squares_bounds.height * heightscale_sm ));
	BR_square2.setScale(widthscale_sm, heightscale_sm);
	BR_square3.setScale(widthscale_sm, heightscale_sm);

	SH_square.setScale(widthscale_sm, heightscale_sm);

	SH_square2.setPosition((WINDOW_WIDTH / 4) + ((shop_menu_bounds.width / 3) * widthscale_sm) + (2*FT_square.getGlobalBounds().width), (WINDOW_HEIGHT / 4) + ((shop_menu_bounds.height / 4) * heightscale_sm) + (5 * upgrade_squares_bounds.height * heightscale_sm));
	SH_square3.setPosition((WINDOW_WIDTH / 4) + ((shop_menu_bounds.width / 3) * widthscale_sm) + (4*FT_square.getGlobalBounds().width), (WINDOW_HEIGHT / 4) + ((shop_menu_bounds.height / 4) * heightscale_sm) + (5 * upgrade_squares_bounds.height * heightscale_sm));
	SH_square2.setScale(widthscale_sm, heightscale_sm);
	SH_square3.setScale(widthscale_sm, heightscale_sm);

	auto FT_curr_square = FT_square;
	auto BR_curr_square = BR_square;
	auto SH_curr_square = SH_square;

	Texture yes_buttont, no_buttont;
	yes_buttont.loadFromFile("Sprites/yes_button.png");
	no_buttont.loadFromFile("Sprites/no_button.png");
	Sprite yes_button(yes_buttont), no_button(no_buttont);
	yes_button.setScale(widthscale_nb * 0.75, heightscale_nb * 0.75);
	no_button.setScale(widthscale_nb * 0.75, heightscale_nb * 0.75);
	PURCHASE.setPosition((float)(WINDOW_WIDTH / 100) * 63, ((float)(WINDOW_HEIGHT / 100) * 60 ));
	yes_button.setPosition((float)(WINDOW_WIDTH / 100) * 63, ((float)(WINDOW_HEIGHT / 100) * 65 ));
	no_button.setPosition((float)(WINDOW_WIDTH / 100) * 69, ((float)(WINDOW_HEIGHT / 100) * 65 ));


	Texture RocketFlametext;
	RocketFlametext.loadFromFile("Sprites/rocket_fire_spritesheet.png");
	Sprite RocketFlame(RocketFlametext);
	RocketFlame.setTextureRect(sf::IntRect(0, 0, 60, 105));
	RocketFlame.setPosition(PlayerRocket.body.getPosition().x, PlayerRocket.body.getPosition().y - PlayerRocket.body.getSize().y);
	//RocketFlame.setScale(widthscale_R * 0.75, heightscale_R * 0.75);
	//RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, RocketFlame.getTextureRect().height / 2);

	bool RF_state = false;

	sf::Vector2i RocketFlameSpritePosition(0,0);


	std::pair <std::vector<std::vector<Obstacle>>, std::vector<sf::Texture>> obstacles_and_textures;

	bool collisionchecker = false;
	//bool proj_collisioncheck, proj_2collisioncheck = false;

	Texture hittext;
	hittext.loadFromFile("Sprites/hit.png");
	sf::Sprite hit(hittext), hit2(hittext);
	hit.setScale(sf::Vector2f( (WINDOW_WIDTH / 15) / hittext.getSize().x, (WINDOW_HEIGHT / 15) / hittext.getSize().y));
	hit2.setScale(sf::Vector2f( (WINDOW_WIDTH / 15) / hittext.getSize().x, (WINDOW_HEIGHT / 15) / hittext.getSize().y));
	bool proj1_hit = false; 
	bool proj2_hit = false;



	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			Vector2i pos = Mouse::getPosition(window);
			switch (event.type)
			{
				case sf::Event::Closed: {
					window.close();
					break;
				}
				case sf::Event::MouseButtonReleased: {
					if(event.mouseButton.button == Mouse::Left) {
						if(startbutton.getGlobalBounds().contains(pos.x, pos.y)) {
							at_titlescreen = false;
							in_game = true;
						}
						else if(loadbutton.getGlobalBounds().contains(pos.x, pos.y)) {
							at_titlescreen = false;
							loadgame_screen = true;
						}

					}
					break;
				}
				case sf::Event::Resized: {
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
       				window.setView(sf::View(visibleArea));
					PlayerRocket.WINDOW_HEIGHT = event.size.height;
					PlayerRocket.WINDOW_WIDTH = event.size.width;
					small_unit_height = event.size.height / 100;
					small_unit_width = event.size.width / 100;

					break;
				}

			    default: {
					break;
				}
			}
		}

		window.clear(sf::Color(150, 150, 150));
		if(at_titlescreen) {
		window.draw(background);
		window.draw(startbutton);
		window.draw(loadbutton);
		window.display();
		}

		else if(in_game) {


			if(starting_newgame) {
			music.play();
			music.setLoop(true);
			window.draw(gamebackground);
			PlayerRocket.body.setPosition(sf::Vector2f((WINDOW_WIDTH / 2), 1.65 * WINDOW_HEIGHT / 2));
			window.draw(PlayerRocket.body);
			window.display();
			/*add text box at the top that explains the controls for the game (space to hit power bar,
			arrow keys to move rocket, collect coins and rocket fuel for upgrades to further explore the horizon)
			along with a "next" button. After these 2-4 text messages are displayed with next button, write a
			"press any key to continue" message to actually start the game*/
			sleep(seconds(0.3));
			window.clear();
			window.draw(gamebackground);
			PlayerRocket.body.setPosition(sf::Vector2f((WINDOW_WIDTH / 2), 1.65 * WINDOW_HEIGHT / 2));
			window.draw(PlayerRocket.body);
			window.draw(DialogBox);
			window.display();
			starting_newgame = false;
			//write_instructions(WINDOW_WIDTH, WINDOW_HEIGHT);


			//WRITING ONTO DIALOG BOX
			//
			//
			//
			std::vector<std::string> message(4);

			//float letterspacing
			message[0] = "Welcome to Rocket Space. In this game, you collect coins and rocket fuel while maneuvering your rocket through the air.";
			message[1] = "These collectables allow you to purchase upgrades for your rocket in the shop, so that you can further explore the horizon";
			message[2] = "Use space bar to time the initial launch power for your rocket, and use the arrow keys to move.";
			message[3] = "Good Luck!";
			Text sent1, sent2, sent3;
			Font font;
			font.loadFromFile("Fonts/Pixeboy-z8XGD.ttf");
			sent1.setFont(font);
			sent2.setFont(font);
			sent3.setFont(font);
			sent1.setCharacterSize((float)(WINDOW_HEIGHT / 20));
			sent2.setCharacterSize((float)(WINDOW_HEIGHT / 20));
			sent3.setCharacterSize((float)(WINDOW_HEIGHT / 20));
			sent1.setFillColor(Color::White);
			sent2.setFillColor(Color::White);
			sent3.setFillColor(Color::White);


			/*for(unsigned int i =0; i < message.size(); i++) {
				for(unsigned int j = 0; j < message[i].size(); i++) {

				}
			}*/

			unsigned int i =0;

			while( i < message.size()) {
			sent1.setString("");
			sent2.setString("");
			sent3.setString("");

			std::string templine;
			std::string templine2;
			int j =1;

			if(message[i].size() > 85) {
				//auto begin = message.begin();
				if(message[i].size() > 170) {
					std::string temp_str2(message[i].begin() + 85, message[i].begin() + 170);
					templine2 = temp_str2;
					std::string temp_str3(message[i].begin() + 170, message[i].end());
					message[i] = temp_str3;
					j = 3;
				}
				std::string temp_str(message[i].begin(), message[i].begin() + 85);
				templine = temp_str;

				if(message[i].size() <= 170) {
				std::string temp_str2(message[i].begin() + 85, message[i].end());
				message[i] = temp_str2;
				j = 2;
				}

			}

			if(j == 1) {
			 sent1.setPosition((WINDOW_WIDTH / 50), (WINDOW_HEIGHT / 40));
			}
			else if(j == 2) {
			 sent1.setPosition((WINDOW_WIDTH / 50), (WINDOW_HEIGHT / 40));
			 sent2.setPosition((WINDOW_WIDTH / 50), (WINDOW_HEIGHT / 40) * 4);
			}
			else {
			sent1.setPosition((WINDOW_WIDTH / 50), (WINDOW_HEIGHT / 40));
			 sent2.setPosition((WINDOW_WIDTH / 50), (WINDOW_HEIGHT / 40) * 4);
			 sent3.setPosition((WINDOW_WIDTH / 50), (WINDOW_HEIGHT / 40) * 8);
			}


			if(j == 1) {
			sent1.setString(message[i]);
			}
			else if(j == 2) {
			  sent1.setString(templine);
			  sent2.setString(message[i]);
			}
			else  {
			  sent1.setString(templine);
			  sent2.setString(templine2);
			  sent3.setString(message[i]);
			}
			//if(j == 1) {
			window.clear();
			window.draw(gamebackground);
			//PlayerRocket.body.setPosition(sf::Vector2f((WINDOW_WIDTH / 2), 1.51 * WINDOW_HEIGHT / 2));
			window.draw(PlayerRocket.body);
			window.draw(DialogBox);
			window.draw(sent1);
			window.draw(sent2);
			window.draw(sent3);
			window.display();
			sleep(seconds(8));

			//}
			/*else if(j == 2) {
			window.clear();
			window.draw(gamebackground);
			PlayerRocket.body.setPosition(sf::Vector2f((WINDOW_WIDTH / 2), 1.51 * WINDOW_HEIGHT / 2));
			window.draw(PlayerRocket.body);
			window.draw(DialogBox);
			window.draw(sent1);
			window.draw(sent2);
			window.display();
			sleep(seconds(1));
			}
			else  {
				window.clear();
				window.draw(gamebackground);
				PlayerRocket.body.setPosition(sf::Vector2f((WINDOW_WIDTH / 2), 1.51 * WINDOW_HEIGHT / 2));
				window.draw(PlayerRocket.body);
				window.draw(DialogBox);
				window.draw(sent1);
				window.draw(sent2);
				window.draw(sent3);
				window.display();
				sleep(seconds(1));
			}*/

			i++;
			}

			window.clear();
			window.draw(gamebackground);
			//PlayerRocket.body.setPosition(sf::Vector2f((WINDOW_WIDTH / 2), 1.51 * WINDOW_HEIGHT / 2));
			window.draw(PlayerRocket.body);
			window.display();
			sleep(seconds(1));




			}  //end of "if starting new game" loop


			//-----------------------------------------------------------
			//-----------------------------------------------------------
			//-----------------------------------------------------------

			//clock.restart();


			damage_state = false;

			if(PlayerRocket.get_FTUPNUM() == 0) {
				FT_text.setString("Increase airtime:\nIncrease Fuel tank\nsize by 30%\n\nCost: 250  Metal");
				FT_square.setFillColor(Color::White); //turn white instead
			}
			if(PlayerRocket.get_FTUPNUM() == 1) {
				//FT_text.setString("Increase airtime:\nIncrease Fuel tank\nsize by 25%\n\nCost: 750  ");
				FT_square2.setFillColor(Color::White);
			}
			if(PlayerRocket.get_FTUPNUM() == 2) {
				//FT_text.setString("Increase airtime:\nIncrease Fuel tank\nsize by 20%\n\nCost: 1200  ");
				FT_square3.setFillColor(Color::White);

			}


			if(PlayerRocket.get_BRUPNUM() == 0) {
				BR_text.setString("Increase speed:\nIncrease Rocket\nBoosters strength by\n20%\n\nCost: 250  Coins");
				BR_square.setFillColor(Color::White);
			}
			if(PlayerRocket.get_BRUPNUM() == 1) {
				//BR_text.setString("Increase speed:\nIncrease Rocket\nBoosters strength by\n15%\n\nCost: 750  ");
				BR_square2.setFillColor(Color::White);
			}
			if(PlayerRocket.get_BRUPNUM() == 2) {
				//BR_text.setString("Increase speed:\nIncrease Rocket\nBoosters strength by\n10%\n\nCost: 1200  ");
				BR_square3.setFillColor(Color::White);
			}


			if(PlayerRocket.get_SHUPNUM() == 0) {
				SH_text.setString("Shooter Upgrade:\nEach shot does 30%\nmore damage\n\nCost: 150 Coins\n\t \t \t  150 Metal");
				SH_square.setFillColor(Color::White);
			}
			if(PlayerRocket.get_SHUPNUM() == 1) {
				//SH_text.setString("Shooter Upgrade:\nTwin Shooters. Two\nshots instead of one\n\nCost: 450      450      ");
				SH_square2.setFillColor(Color::White);
			}
			if(PlayerRocket.get_SHUPNUM() == 2) {
				//SH_text.setString("Shooter Upgrade:\nEach shot does\n10% more damage\n\nCost: 500    500    ");
				SH_square3.setFillColor(Color::White);
			}

			//music.play();


		 	coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
			fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
			//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));

			Texture Coin_t, FuelTankt;
			Coin_t.loadFromFile("Sprites/coin_sprite.png");
			FuelTankt.loadFromFile("Sprites/Metal.png");

			Sprite Coin_icon(Coin_t), FuelTank_icon(FuelTankt);

			float heightscale_ci = ((float)(WINDOW_HEIGHT / 100) * 3.2 ) / Coin_t.getSize().y;
			float widthscale_ci = ((float)(WINDOW_WIDTH / 100) * 2.1 ) / Coin_t.getSize().x;


			float heightscale_fti = ((float)(WINDOW_HEIGHT / 100) * 3.2 ) / FuelTankt.getSize().y;
			float widthscale_fti = ((float)(WINDOW_WIDTH / 100) * 2.1 ) / FuelTankt.getSize().x;


			Coin_icon.setScale(widthscale_ci, heightscale_ci);
			FuelTank_icon.setScale(widthscale_fti, heightscale_fti);

			//originally 70 and 80 x pos
			Coin_icon.setPosition((float)(WINDOW_WIDTH / 100) * 75, ((float)(WINDOW_HEIGHT / 100) * 3 ));
			FuelTank_icon.setPosition((float)(WINDOW_WIDTH / 100) * 90, ((float)(WINDOW_HEIGHT / 100) * 3 ));



			window.clear();
			if(game.altitude <= 90) {
				gamebackground.setTexture(gamebackgroundt, true);
				gamebackground.setScale(widthscale_gb, heightscale_gb);
				game.altitude = 0;
			}
			window.draw(gamebackground);
			window.draw(Coin_icon);
			window.draw(FuelTank_icon);
			window.draw(coincount);
			window.draw(fueltankcount);
			//window.draw(score);
			PlayerRocket.body.setTexture(&Rockett, true);
			PlayerRocket.body.setPosition(sf::Vector2f((WINDOW_WIDTH / 2), 1.65 * WINDOW_HEIGHT / 2));
			PlayerRocket.body.setSize(sf::Vector2f((float)Rockett.getSize().x, (float)Rockett.getSize().y));
			PlayerRocket.body.setScale(widthscale_R, heightscale_R);
			PlayerRocket.health = 2;
			window.draw(PlayerRocket.body);
			Texture PBt;
			PBt.loadFromFile("Sprites/Powerbars_spritesheet.png");

			PBAnimation powerbar(&PBt, sf::Vector2u(10,1), WINDOW_WIDTH, WINDOW_HEIGHT);
			window.clear();
			//sf::View view(powerbar.GetPosition(), powerbar.GetSize());
			//view.setCenter(powerbar.GetPosition());
			//window.draw(powerbar.GetBody());
			//window.display();
			//sleep(seconds(0.08));
			while( (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == false) ) {
				window.draw(gamebackground);
				window.draw(Coin_icon);
				window.draw(FuelTank_icon);
				coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
				window.draw(coincount);
				window.draw(fueltankcount);
				fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
				//.draw(score);
				//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));
				PlayerRocket.body.setPosition(sf::Vector2f((WINDOW_WIDTH / 2), 1.65 * WINDOW_HEIGHT / 2));
				window.draw(PlayerRocket.body);
				powerbar.Update();
				window.draw(powerbar.GetBody());
				window.display();
				sleep(seconds(0.03));
				window.clear();
			}

			//COMMENT THIS OUT LATER
			////////////////////////////////
			////////////////////////////////
			////////////////////////////////

			game.altitude = 0;



			////////////////////////////////
			////////////////////////////////
			////////////////////////////////



			sf::SoundBuffer buffer;

			if (!buffer.loadFromFile("Sounds/Rocket_hurt.wav"))
				return -1;

			sf::Sound sound;
			sound.setBuffer(buffer);



			clock.restart();

			PlayerRocket.setLaunchSpeed(powerbar.ReturnRocketSpeed());

			Texture Rockett2;
			float heightscale_R = (float)(WINDOW_HEIGHT / 12) / 60;
			float widthscale_R = (float)(WINDOW_WIDTH / 24) / 60;
			std::string RocketTexture;


			if(PlayerRocket.num_type == 1) {
			//Rockett2.loadFromFile("Sprites/Rocket_1.png");
			RocketTexture = "Sprites/Rocket_1.png";
			}
			else if(PlayerRocket.num_type == 2) {
			//Rockett2.loadFromFile("Sprites/Rocket_2.png");
			RocketTexture = "Sprites/Rocket_2.png";
			}

			//RocketTexture = "Sprites/Rocket_1.png";

			Rockett2.loadFromFile(RocketTexture);
			PlayerRocket.body.setTexture(&Rockett2, true);

			PlayerRocket.body.setSize(sf::Vector2f(60, 60));
			PlayerRocket.body.setScale(widthscale_R, heightscale_R);


			Texture go_upt;
			go_upt.loadFromFile("Sprites/Up_sprite.png");
			Sprite go_up(go_upt);
			go_up.setScale(widthscale_R * 0.75, heightscale_R* 0.75);
			go_up.setPosition(-10, WINDOW_HEIGHT / 4);
			sf::Clock flameclock;
			alt_count = 0;



			while((PlayerRocket.health > 0) && (PlayerRocket.fuel > 0) ) {

				/*while(window.pollEvent(event)) {

				 if(event.type == sf::Event::KeyPressed) {
					 if(event.key.code == sf::Keyboard::Up ||event.key.code == sf::Keyboard::Down ||
					 event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left) {
						 PlayerRocket.Control_Rocket();
					 }
					 if(event.key.code == sf::Keyboard::Space) {
						 	PlayerRocket.move_projectile();
					 }
				 }

				}*/

				PlayerRocket.Control_Rocket(boss_time);



				//view.setCenter(PlayerRocket.body.getPosition());


				//projectile code


				/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if(!PlayerRocket.proj_thrown1) {
					PlayerRocket.proj1.setPosition(PlayerRocket.body.getPosition());
					PlayerRocket.proj_thrown1 = true;
				}
				else if(!PlayerRocket.proj_thrown2) {
					PlayerRocket.proj2.setPosition(PlayerRocket.body.getPosition());
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

			PlayerRocket.move_projectile();
			PlayerRocket.body.setOrigin(PlayerRocket.body.getSize().x / 2, PlayerRocket.body.getSize().y / 2 );
			if(clock.getElapsedTime().asSeconds() <= 1.8 && damage_state == true) {
					if(  alt_count % 2 == 0) {
						hurt_animation(PlayerRocket, widthscale_R, heightscale_R, false);
						alt_count++;
					}
					else {
						hurt_animation(PlayerRocket, widthscale_R, heightscale_R, true);
						alt_count++;
					}
				}
				else {
					hurt_animation(PlayerRocket, widthscale_R, heightscale_R, false);
				}


				if(PlayerRocket.body.getGlobalBounds().top < 0) {
					game.altitude += 10;
					int diff = WINDOW_HEIGHT - PlayerRocket.body.getSize().y;
					PlayerRocket.body.move(0, diff);
					obstacles_and_textures = Change_Screen(gamebackground, game, WINDOW_WIDTH, WINDOW_HEIGHT);
					gamebackground.setTexture(obstacles_and_textures.second[0], true);
					gamebackground.setScale(widthscale_gb, heightscale_gb);
				}
				/*else if( (PlayerRocket.body.getGlobalBounds().top > WINDOW_HEIGHT) && (game.altitude != 0)) {
					game.altitude -= 10;
					obstacles_and_textures = Change_Screen(gamebackground, game, WINDOW_WIDTH, WINDOW_HEIGHT);

				}*/
				if((game.altitude % 100 == 0) && (game.altitude > 0)) {
					if(game.altitude == 100 && (boss1_defeated == false)) {
						boss_num = 1;
					}
					else if(game.altitude == 200) {
						boss_num = 2;
					}
					else if(game.altitude == 300) {
						boss_num = 3;
					}
					else {
						boss_num = 4;
					}
					if( (PlayerRocket.body.getGlobalBounds().top < WINDOW_HEIGHT / 1.5) && (!boss_time) &&
					PlayerRocket.num_type == 1) {

						create_boss(Boss, boss_num, WINDOW_WIDTH, WINDOW_HEIGHT);
						PlayerRocket.proj1.setPosition(0, -10.0f);
						PlayerRocket.proj2.setPosition(0, -10.0f);
						window.clear();
						window.draw(gamebackground);
						window.draw(Coin_icon);
						window.draw(FuelTank_icon);
						window.draw(coincount);
						coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
						window.draw(fueltankcount);
						fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
						//window.draw(score);
						//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));
						window.draw(PlayerRocket.body);
						window.draw(Boss.body);

						window.display();
						sleep(seconds(2));

						Text sent1;
						Font font;
						font.loadFromFile("Fonts/Pixeboy-z8XGD.ttf");
						sent1.setFont(font);
						sent1.setFillColor(Color::White);
						sent1.setCharacterSize((float)WINDOW_HEIGHT/25);
						sent1.setPosition(sf::Vector2f(small_unit_width * 42, small_unit_height * 22));
						sent1.setString("I cannot allow you to progress any further");


						window.clear();
						window.draw(gamebackground);
						window.draw(Coin_icon);
						window.draw(FuelTank_icon);
						window.draw(coincount);
						coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
						window.draw(fueltankcount);
						fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
						//window.draw(score);
						//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));
						window.draw(PlayerRocket.body);
						window.draw(Boss.body);
						window.draw(sent1);
						window.display();
						sleep(seconds(5));

						boss_time = true;
						//Bossclock.restart();
					}

				}


				if(boss_time) {

					if(Boss.health <= 0) {
						boss_time = false;
						Text temptext, temptext2;
						String tempstring1;
						tempstring1 = " Congrats!\t\t\tYou defeated Boss " + std::to_string(Boss.enemy_num - 1);
						temptext.setString(tempstring1);
						temptext.setFont(font);
						temptext2.setFont(font);
						temptext2.setString("Unfortunately, your rocket cannot move any further");
						temptext.setFillColor(Color::White);
						temptext2.setFillColor(Color::White);

						temptext.setPosition(45 * small_unit_width, 30 * small_unit_height);
						temptext2.setPosition(45 * small_unit_width, 30 * small_unit_height);

						window.clear();
						window.draw(gamebackground);
						window.draw(Coin_icon);
						window.draw(FuelTank_icon);
						window.draw(coincount);
						coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
						window.draw(fueltankcount);
						fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
						//window.draw(score);
						//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));
						window.draw(PlayerRocket.body);
						window.draw(RocketFlame);
						window.draw(temptext);

						window.display();
						sleep(seconds(3)); // <== change this to 6 secs or somethin later


						window.clear();


						window.draw(gamebackground);
						window.draw(Coin_icon);
						window.draw(FuelTank_icon);
						window.draw(coincount);
						coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
						window.draw(fueltankcount);
						fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
						//window.draw(score);
						//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));
						window.draw(PlayerRocket.body);
						window.draw(RocketFlame);
						window.draw(temptext2);

						window.display();
						sleep(seconds(3)); // <== change this to 6 secs or somethin later


						while(PlayerRocket.fuel > 0) {

							window.clear();


						window.draw(gamebackground);
						window.draw(Coin_icon);
						window.draw(FuelTank_icon);
						window.draw(coincount);
						coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
						window.draw(fueltankcount);
						fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
						//window.draw(score);
						//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));
						window.draw(PlayerRocket.body);
						window.draw(RocketFlame);
						window.display();
						PlayerRocket.fuel -= 10 * PlayerRocket.get_fuelconstant();

										if(PlayerRocket.fuel >= 75) {
										RocketFlame.setTextureRect(sf::IntRect(0, 0, 61, 105));
										//RocketFlame.setScale(0.8, 0.8);
										float temp_width = small_unit_width * 1 / RocketFlame.getTextureRect().width;
										float temp_height = small_unit_height * 5.5 / RocketFlame.getTextureRect().height;
										RocketFlame.setScale(temp_width, temp_height);
										RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);

									}
									else if(PlayerRocket.fuel >= 50) {
										RocketFlame.setTextureRect(sf::IntRect(160, 0, 50, 84));
										float temp_width = small_unit_width * 1 / RocketFlame.getTextureRect().width;
										float temp_height = small_unit_height * 4.5 / RocketFlame.getTextureRect().height;
										RocketFlame.setScale(temp_width, temp_height);
										RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);
									}
									else if(PlayerRocket.fuel >= 25) {
										RocketFlame.setTextureRect(sf::IntRect(320, 0, 30, 51));
										float temp_width = small_unit_width * 1 / RocketFlame.getTextureRect().width;
										float temp_height = small_unit_height * 3.5 / RocketFlame.getTextureRect().height;
										RocketFlame.setScale(temp_width, temp_height);
										RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);
									}
									else if(PlayerRocket.fuel > 5) {
										RocketFlame.setTextureRect(sf::IntRect(480, 0, 13, 20));
										float temp_width = small_unit_width * 1  / RocketFlame.getTextureRect().width;
										float temp_height = small_unit_height * 2.5 / RocketFlame.getTextureRect().height;
										RocketFlame.setScale(temp_width, temp_height);
										RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);

									}

						}


						Texture tempRockettext;
						tempRockettext.loadFromFile("Sprites/rocket_1_rs.png");
						PlayerRocket.body.setTexture(&tempRockettext, true);
						PlayerRocket.body.setScale(widthscale_R, heightscale_R);






						while(PlayerRocket.body.getPosition().y < WINDOW_HEIGHT) {
							PlayerRocket.body.move(0, small_unit_height * 0.6);

						window.clear();
						window.draw(gamebackground);
						window.draw(Coin_icon);
						window.draw(FuelTank_icon);
						window.draw(coincount);
						coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
						window.draw(fueltankcount);
						fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
						//window.draw(score);
						//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));
						window.draw(PlayerRocket.body);
						window.display();
						//sleep(seconds(0.1));
						}

						window.clear();
						sf::RectangleShape blackbackground;
						Texture temptexture;
						temptexture.loadFromFile("Sprites/background.png");
						blackbackground.setTexture(&temptexture, true);
						blackbackground.setSize(sf::Vector2f(600, 400));
						blackbackground.setScale(widthscale_gb, heightscale_gb);

						window.draw(blackbackground);
						window.display();
						gamebackground.setTexture(gamebackgroundt, true);
						gamebackground.setScale(widthscale_gb, heightscale_gb);
						sleep(seconds(2));

						window.clear();
						window.draw(gamebackground);
						window.draw(PlayerRocket.body);
						window.display();
						sleep(seconds(1));

						PlayerRocket.body.move(0, -(97 * small_unit_height));

						while(PlayerRocket.body.getPosition().y < (1.65 * WINDOW_HEIGHT / 2)) {
							PlayerRocket.body.move(0, small_unit_height * 0.6);
							window.clear();
							window.draw(gamebackground);
							//window.draw(Coin_icon);
							//window.draw(FuelTank_icon);
							//window.draw(coincount);
							//coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
							//window.draw(fueltankcount);
							//fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
							//window.draw(score);
							//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));
							window.draw(PlayerRocket.body);
							window.display();
						}

						sleep(seconds(2));

						String tempstring2;
						tempstring1 = " You'll need a different rocket to continue...";
						tempstring2 = "Look no further!";

							temptext.setString(tempstring1);

							window.clear();
							window.draw(gamebackground);
							window.draw(PlayerRocket.body);
							window.draw(temptext);
							window.display();
							sleep(seconds(2.5));

						temptext2.setString(tempstring2);


							window.clear();
							window.draw(gamebackground);
							window.draw(PlayerRocket.body);
							window.draw(temptext2);
							window.display();
							sleep(seconds(2.5));

						/*PlayerRocket.body.setTexture(&Rockett2, true);
						PlayerRocket.body.setScale(widthscale_R, heightscale_R);*/

							clock.restart();
							bool tempbool = true;
							while(clock.getElapsedTime().asSeconds() < 3) {
								hurt_animation(PlayerRocket, widthscale_R, heightscale_R, tempbool);

								if(tempbool == true) {
									tempbool = false;
								}
								else {
									tempbool = true;
								}
								window.clear();
								window.draw(gamebackground);
								window.draw(PlayerRocket.body);
								window.draw(temptext2);
								window.display();
								sleep(seconds(0.1));

							}


							/*Rockett2.loadFromFile("Sprites/Rocket_2.png");
							PlayerRocket.body.setTexture(&Rockett2, true);
							PlayerRocket.body.setScale(widthscale_R, heightscale_R);
							sleep(seconds(2));*/

							temptexture.loadFromFile("Sprites/new_rocket_screen.png");
							Sprite tempscreen;
							tempscreen.setTexture(temptexture, true);
							tempscreen.setScale(widthscale_sm, heightscale_sm);
							tempscreen.setPosition((WINDOW_WIDTH / 4), (WINDOW_HEIGHT / 4));


							bool boolean_continue = false;
							sf::Event event2;
							Texture next_button_popt;

							next_button_popt.loadFromFile("Sprites/Next_button_pop.png");


							while(boolean_continue == false) {

								while(window.pollEvent(event2)) {
										Vector2i pos = Mouse::getPosition(window);
										switch (event2.type) {
										case sf::Event::MouseMoved:

										if(next_button.getGlobalBounds().contains(pos.x, pos.y)) {
												next_button.setTexture(next_button_popt, true);
												next_button.setScale(widthscale_nb, heightscale_nb);
												break;
										}

										next_button.setTexture(next_buttont, true);
										next_button.setScale(widthscale_nb, heightscale_nb);
										break;

										case sf::Event::MouseButtonReleased:
										if(event2.mouseButton.button == Mouse::Left) {
										if(next_button.getGlobalBounds().contains(pos.x, pos.y)) {
											boolean_continue = true;
											break;
										}
										}

										default:
											break;
										}
								}
										window.clear();
										window.draw(gamebackground);
										window.draw(tempscreen);
										window.draw(next_button);
										window.display();

							}

							Rockett2.loadFromFile("Sprites/Rocket_2.png");
							PlayerRocket.body.setTexture(&Rockett2, true);
							PlayerRocket.body.setScale(widthscale_R, heightscale_R);
							PlayerRocket.upgrade_rocket();
							/*window.clear();
							window.draw(gamebackground);
							window.draw(PlayerRocket.body);
							window.display();
							sleep(seconds(2));*/

							boss_time = false;
							boss1_defeated = true;
							game.altitude = 0;
							FT_square.setFillColor(Color::White);
							FT_square2.setFillColor(Color::White);
							FT_square3.setFillColor(Color::White);

							BR_square.setFillColor(Color::White);
							BR_square2.setFillColor(Color::White);
							BR_square3.setFillColor(Color::White);

							SH_square.setFillColor(Color::White);
							SH_square2.setFillColor(Color::White);
							SH_square3.setFillColor(Color::White);

							FT_curr_square = FT_square;
							BR_curr_square = BR_square;
							SH_curr_square = SH_square;

							FT_text.setString("Increase airtime:\nIncrease Fuel tank\nsize by 25%\n\nCost: 650  Metal");
							BR_text.setString("Increase speed:\nIncrease Rocket\nBoosters strength by\n15%\n\nCost: 650  Coins");
							SH_text.setString("Shooter Upgrade:\nEach shot does 25%\nmore damage\n\nCost: 500 Coins\n\t \t \t  500 Metal");

					}
					//end of boss defeated sequence


				
					proj1_hit = PlayerRocket.GetColliderProj1().CheckCollision(Boss.GetCollider(), 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
					if(proj1_hit) {
						Boss.health -= PlayerRocket.rocket_damage;
						hit.setPosition(Boss.body.getPosition());
						PlayerRocket.proj_thrown1 = false;
						PlayerRocket.proj1.setPosition(0, -100.0f);


						//proj1_hit = true;

					}
					proj2_hit = PlayerRocket.GetColliderProj2().CheckCollision(Boss.GetCollider(), 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
					if(proj2_hit) {
						Boss.health -= PlayerRocket.rocket_damage;
						hit2.setPosition(Boss.body.getPosition());
						PlayerRocket.proj_thrown2 = false;
						PlayerRocket.proj2.setPosition(0, -100.0f);
						//proj2_hit = true;
					}
					collisionchecker = PlayerRocket.GetCollider().CheckCollision(Boss.GetCollider(), 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
					if(collisionchecker && clock.getElapsedTime().asSeconds() > 2) {
									damage_state = true;
									PlayerRocket.health -= 1;
									hurt_animation(PlayerRocket, widthscale_R, heightscale_R, true);
									sound.play();
									clock.restart();
					}


				}


				//end of boss sequence
				////
				///


				if(!obstacles_and_textures.first.empty()) {
					for(unsigned int i =0; i < obstacles_and_textures.first.size(); ++i) {
						for(unsigned int j =0; j < obstacles_and_textures.first[i].size(); ++j) {
							//collisionchecker = obstacles_and_textures.first[i][j].GetCollider().CheckCollision(PlayerRocket.GetCollider(), 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
							if( abs(obstacles_and_textures.first[i][j].body.getPosition().x - PlayerRocket.body.getPosition().x) > WINDOW_WIDTH / 28) {
								continue;
							}
							if( abs(obstacles_and_textures.first[i][j].body.getPosition().y - PlayerRocket.body.getPosition().y) > WINDOW_HEIGHT / 14) {
								continue;
							}
							collisionchecker = PlayerRocket.GetCollider().CheckCollision(obstacles_and_textures.first[i][j].GetCollider(), 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);

							if(collisionchecker) {
								if( (i == 0) && (clock.getElapsedTime().asSeconds() > 2)) {
									damage_state = true;
									PlayerRocket.health -= 1;
									hurt_animation(PlayerRocket, widthscale_R, heightscale_R, true);
									sound.play();
									clock.restart();

								}
								else if(i == 1) {
									PlayerRocket.increase_coinscollected();
									obstacles_and_textures.first[1].erase(obstacles_and_textures.first[1].begin() + j);
								}
								else if(i == 2) {
									PlayerRocket.increase_fuelcollected();
									obstacles_and_textures.first[2].erase(obstacles_and_textures.first[2].begin() + j);
								}
							}


						}
					}
				}



				window.clear();
				window.draw(gamebackground);
				window.draw(Coin_icon);
				window.draw(FuelTank_icon);
				window.draw(coincount);
				coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
				window.draw(fueltankcount);
				fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
				//window.draw(score);
				//score.setString("Score: " + std::to_string(PlayerRocket.get_score()));

				if(!obstacles_and_textures.first.empty()) {
					for(unsigned int i =0; i < obstacles_and_textures.first.size(); i++) {
						for(unsigned int j =0; j < obstacles_and_textures.first[i].size(); j++) {
							window.draw(obstacles_and_textures.first[i][j].body);
						}
				}

				}





				window.draw(PlayerRocket.body);
				if(PlayerRocket.proj_thrown1) {
					window.draw(PlayerRocket.proj1);
				}
				if(PlayerRocket.proj_thrown2) {
					window.draw(PlayerRocket.proj2);
				}

				if(game.altitude == 0 && clock.getElapsedTime().asSeconds() > 2 && display_up == true) {
					if(go_up.getPosition().x < WINDOW_WIDTH / 12) {
						go_up.move(5.0f, 0);
					}
					window.draw(go_up);
				}

				if(PlayerRocket.fuel >= 75) {
					RocketFlame.setTextureRect(sf::IntRect(0, 0, 61, 105));
					//RocketFlame.setScale(0.8, 0.8);
					float temp_width = small_unit_width * 1 / RocketFlame.getTextureRect().width;
					float temp_height = small_unit_height * 5.5 / RocketFlame.getTextureRect().height;
					RocketFlame.setScale(temp_width, temp_height);
					RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);

				}
				else if(PlayerRocket.fuel >= 50) {
					RocketFlame.setTextureRect(sf::IntRect(160, 0, 50, 84));
					float temp_width = small_unit_width * 1 / RocketFlame.getTextureRect().width;
					float temp_height = small_unit_height * 4.5 / RocketFlame.getTextureRect().height;
					RocketFlame.setScale(temp_width, temp_height);
					RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);
				}
				else if(PlayerRocket.fuel >= 25) {
					RocketFlame.setTextureRect(sf::IntRect(320, 0, 30, 51));
					float temp_width = small_unit_width * 1 / RocketFlame.getTextureRect().width;
					float temp_height = small_unit_height * 3.5 / RocketFlame.getTextureRect().height;
					RocketFlame.setScale(temp_width, temp_height);
					RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);
				}
				else if(PlayerRocket.fuel > 5) {
					RocketFlame.setTextureRect(sf::IntRect(480, 0, 13, 20));
					float temp_width = small_unit_width * 1  / RocketFlame.getTextureRect().width;
					float temp_height = small_unit_height * 2.5 / RocketFlame.getTextureRect().height;
					RocketFlame.setScale(temp_width, temp_height);
					RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);

				}
				if(RF_state != true && flameclock.getElapsedTime().asSeconds() > 0.4) {
					/*int tempx, tempy;
					tempx = RocketFlameSpritePosition.x*/
					RocketFlame.setTextureRect(sf::IntRect(RocketFlameSpritePosition.x + 80, 0,
					RocketFlame.getTextureRect().width, RocketFlame.getTextureRect().height));
					RF_state = true;
					flameclock.restart();
					RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);

				}
				else if(RF_state == true && flameclock.getElapsedTime().asSeconds() > 0.4) {
					RocketFlame.setTextureRect(sf::IntRect(RocketFlameSpritePosition.x - 80, 0,
					RocketFlame.getTextureRect().width, RocketFlame.getTextureRect().height));
					RF_state = false;
					flameclock.restart();
					RocketFlame.setOrigin(RocketFlame.getTextureRect().width / 2, 0);
				}
				RocketFlame.setPosition(PlayerRocket.body.getPosition().x, PlayerRocket.body.getPosition().y + (PlayerRocket.body.getSize().y / 2));
				//RocketFlame.setPosition(PlayerRocket.body.getPosition().x, PlayerRocket.body.getPosition().y + (PlayerRocket.body.getSize().y / 2));
				window.draw(RocketFlame);
				if(boss_time) {
					attack_finished = Boss.boss_attack(attack_finished);
					Boss.Draw(window);
				}
				
				
				if(proj1_hit) {
					window.draw(hit);
					proj1_hit = false;
				}
				if(proj2_hit) {
					window.draw(hit2);
					proj2_hit = false;
				}
				window.display();


			}

			sleep(seconds(1));
			display_up = false;

			window.clear();
			window.draw(gamebackground);
			window.draw(Coin_icon);
			window.draw(FuelTank_icon);
			window.draw(coincount);
			window.draw(fueltankcount);
			//window.draw(score);

			window.draw(FT_square);
			window.draw(BR_square);
			window.draw(SH_square);

			window.draw(shop_menu);
			window.draw(next_button);

			window.display();
			Texture next_button_popt;

			next_button_popt.loadFromFile("Sprites/Next_button_pop.png");

			bool boolean_continue = false;
			int purchase_text_app = 0;
			int draw_upgrade = 0;

			sf::Event event2;


				while(boolean_continue == false) {
				while(window.pollEvent(event2)) {

					Vector2i pos = Mouse::getPosition(window);
					switch (event2.type) {

					case sf::Event::MouseMoved:
						if(next_button.getGlobalBounds().contains(pos.x, pos.y)) {
								next_button.setTexture(next_button_popt, true);
								next_button.setScale(widthscale_nb, heightscale_nb);
								break;
							}
						//FT_curr_square from FT_square
						if(FT_curr_square.getGlobalBounds().contains(pos.x, pos.y) && (purchase_text_app == 0)) {
								draw_upgrade = 1;
						}
						 else if(BR_curr_square.getGlobalBounds().contains(pos.x, pos.y) && (purchase_text_app == 0)) {
							draw_upgrade = 2;

						}
						 else if(SH_curr_square.getGlobalBounds().contains(pos.x, pos.y) && (purchase_text_app == 0)) {
							draw_upgrade = 3;

						}
						else if(purchase_text_app != 0) {

						}
						else {
							draw_upgrade = 0;

						}

						next_button.setTexture(next_buttont, true);
						next_button.setScale(widthscale_nb, heightscale_nb);
						break;

					case sf::Event::MouseButtonReleased:
						if(event2.mouseButton.button == Mouse::Left) {
							if(next_button.getGlobalBounds().contains(pos.x, pos.y)) {
								boolean_continue = true;
							}
							else if(FT_curr_square.getGlobalBounds().contains(pos.x, pos.y)) {
									if((PlayerRocket.fuel_coll >= 250) && (PlayerRocket.get_FTUPNUM() == 0)) {
												purchase_text_app = 1;
												draw_upgrade = 1;
									}
									else if((PlayerRocket.fuel_coll >= 650) && (PlayerRocket.get_FTUPNUM() == 1)) {
										purchase_text_app = 2;
										draw_upgrade = 1;

									}
									else if((PlayerRocket.fuel_coll >= 1000) && (PlayerRocket.get_FTUPNUM() == 2)) {
										purchase_text_app = 3;
										draw_upgrade = 1;

									}



							}
							else if(BR_curr_square.getGlobalBounds().contains(pos.x, pos.y)) {
									if((PlayerRocket.coins_coll >= 250) && (PlayerRocket.get_BRUPNUM() == 0)) {
											purchase_text_app = 4;
											draw_upgrade = 2;

									}
									else if((PlayerRocket.coins_coll >= 650) && (PlayerRocket.get_BRUPNUM() == 1)) {
											purchase_text_app = 5;
											draw_upgrade = 2;

									}
									else if((PlayerRocket.coins_coll >= 1000) && (PlayerRocket.get_BRUPNUM() == 2)) {
											purchase_text_app = 6;
											draw_upgrade = 2;
									}

							}
							else if(SH_curr_square.getGlobalBounds().contains(pos.x, pos.y)) {
									if( (PlayerRocket.coins_coll >= 150 && PlayerRocket.fuel_coll >= 150 ) && (PlayerRocket.get_SHUPNUM() == 0)) {

											purchase_text_app = 7;
											draw_upgrade = 3;
									}
									else if((PlayerRocket.coins_coll >= 450 && PlayerRocket.fuel_coll >= 450 ) && (PlayerRocket.get_SHUPNUM() == 1)) {
											purchase_text_app = 8;
											draw_upgrade = 3;
									}
									else if((PlayerRocket.coins_coll >= 500 && PlayerRocket.fuel_coll >= 500 ) && (PlayerRocket.get_SHUPNUM() == 2)) {
											purchase_text_app = 9;
											draw_upgrade = 3;
									}
							}

							else if(yes_button.getGlobalBounds().contains(pos.x, pos.y) && purchase_text_app != 0) {
								if(purchase_text_app <= 3) {

									if(purchase_text_app == 1) {
										PlayerRocket.fuel_coll -= 250;
										FT_square.setFillColor(Color::Green);
										FT_curr_square = FT_square2;
										//PlayerRocket.FT_upgrade();
										FT_text.setString("Increase airtime:\nIncrease Fuel tank\nsize by 25%\n\nCost: 650  Metal");
									}
									else if(purchase_text_app == 2) {
										PlayerRocket.fuel_coll -= 650;
										FT_square2.setFillColor(Color::Green);
										FT_curr_square = FT_square3;
										//PlayerRocket.FT_upgrade();
										FT_text.setString("Increase airtime:\nIncrease Fuel tank\nsize by 20%\n\nCost: 1000  Metal");
									}
									else if(purchase_text_app == 3) {
										PlayerRocket.fuel_coll -= 1000;
										FT_square3.setFillColor(Color::Green);
										///PlayerRocket.FT_upgrade();
									}

									PlayerRocket.FT_upgrade();
								}

								else if(purchase_text_app <= 6) {

									if(purchase_text_app == 4) {
										PlayerRocket.coins_coll -= 250;
										BR_square.setFillColor(Color::Green);
										BR_curr_square = BR_square2;
										BR_text.setString("Increase speed:\nIncrease Rocket\nBoosters strength by\n15%\n\nCost: 650  Coins");
									}
									else if(purchase_text_app == 5) {
										PlayerRocket.coins_coll -= 650;
										BR_square2.setFillColor(Color::Green);
										BR_curr_square = BR_square3;
										BR_text.setString("Increase speed:\nIncrease Rocket\nBoosters strength by\n10%\n\nCost: 1000  Coins");

									}
									else if(purchase_text_app == 6) {
										PlayerRocket.coins_coll -= 1000;
										BR_square3.setFillColor(Color::Green);

									}
									PlayerRocket.BR_upgrade();
								}
								else if(purchase_text_app <= 9) {
									if(purchase_text_app == 7) {
										PlayerRocket.coins_coll -= 150;
										PlayerRocket.fuel_coll -= 150;
										SH_square.setFillColor(Color::Green);
										SH_curr_square = SH_square2;
										SH_text.setString("Shooter Upgrade:\nEach shot does 30%\nmore damage\n\nCost: 450 Coins\n\t \t \t  450 Metal");

									}
									else if(purchase_text_app == 8) {
										PlayerRocket.coins_coll -= 450;
										PlayerRocket.fuel_coll -= 450;
										SH_square2.setFillColor(Color::Green);
										SH_curr_square = SH_square3;
										SH_text.setString("Shooter Upgrade:\nEach shot does 25%\nmore damage\n\nCost: 500 Coins\n\t \t \t  500 Metal");
									}
									else if(purchase_text_app == 9) {
										PlayerRocket.coins_coll -= 500;
										PlayerRocket.fuel_coll -= 500;
										SH_square3.setFillColor(Color::Green);
									}
									PlayerRocket.SH_upgrade();
								}
								purchase_text_app = 0;
							}

							else if(no_button.getGlobalBounds().contains(pos.x, pos.y) && purchase_text_app != 0) {
									purchase_text_app = 0;


							}


							break;
						}

					default:
						break;
					}
				//sleep(seconds(1));
			}
			window.clear();
			window.draw(gamebackground);
			window.draw(shop_menu);
			window.draw(next_button);

			window.draw(FT_square);
			window.draw(FT_square2);
			window.draw(FT_square3);
			window.draw(BR_square);
			window.draw(BR_square2);
			window.draw(BR_square3);
			window.draw(SH_square);
			window.draw(SH_square2);
			window.draw(SH_square3);

			window.draw(Coin_icon);
			window.draw(FuelTank_icon);

			coincount.setString("x " + std::to_string(PlayerRocket.get_coinscollected()));
			fueltankcount.setString("x " + std::to_string(PlayerRocket.get_fuelcollected()));
			window.draw(coincount);
			window.draw(fueltankcount);
			//window.draw(score);

			if(draw_upgrade == 1) {
				window.draw(FT_text);
			}
			else if(draw_upgrade == 2) {
				window.draw(BR_text);
			}
			else if(draw_upgrade == 3) {
				window.draw(SH_text);
			}

			if(purchase_text_app != 0) {
				window.draw(PURCHASE);
				window.draw(yes_button);
				window.draw(no_button);
			}

			window.display();
			}





			PlayerRocket.health = 2;
			PlayerRocket.fuel = 100;

			window.clear();
			window.draw(gamebackground); //regular 'background' is The TS
			window.draw(Coin_icon);
			window.draw(FuelTank_icon);
			window.draw(coincount);
			window.draw(fueltankcount);
			//window.draw(score);
			window.display();


			sleep(seconds(1));




		}
		else if(loadgame_screen) {
			/*draw loadscreen, have a long, horizontal textbox drawn on the
			loadscreen where users can type their passwords to resume their progress from their
			last game*/
		}


	}//while window is open
} //end of main()


/*void write_instructions() {
	//write to DB and include next button for user. Make more than one message
	std::vector<std::string> message(4);

	//float letterspacing
	message[0] = "Welcome to Rocket Space. In this game, you collect coins and rocket fuel while maneuvering your rocket through the air.";
	message[1] = "These collectables allow you to purchase upgrades for your rocket in the shop, so that you can further explore the horizon";
	message[2] = "Use space bar to time the initial launch power for your rocket, and use the arrow keys to move.";
	message[3] = "Good Luck!";
	Text text;
	Font font;
	font.loadFromFile("Fonts/pixelated.ttf");
	text.setFont(font);
	text.setCharacterSize((float)(WINDOW_HEIGHT / 12));
	text.setFillColor(Color::White);

	for(unsigned int i =0; i < message.size(); i++) {
		for(unsigned int j = 0; j < message[i].size(); i++) {

		}
	}
	text.setPosition((WINDOW_WIDTH / 10), (WINDOW_HEIGHT / 15));
	text.setString(message[0]);
	window.draw(text);
	window.display();





}*/



std::pair <std::vector<std::vector<Obstacle>>, std::vector<sf::Texture>> Change_Screen(Sprite& gamebackground, Game& game, float WINDOW_WIDTH, float WINDOW_HEIGHT)  {
	Texture temptext;
	std::string temp_str;
	int quotient = 1;
	int remainder = game.altitude;
	bool boss_time = false;

	if( (remainder % 100 == 0) && (remainder > 0)) {
		boss_time = true;
	}

	while(remainder > 90 && (remainder % 100 != 0) ) {
		quotient++;
		remainder = remainder - 90;
	}

	if(remainder <= 90 && remainder > 60) {
			remainder = 3;
	}
	else if(remainder <= 60 && remainder > 30) {
			remainder = 2;
	}
	else {
			remainder = 1;
	}
	temptext.loadFromFile("Sprites/background_" + std::to_string(quotient) + "_" + std::to_string(remainder) + ".png" );
	float heightscale_gb = (float)WINDOW_HEIGHT / temptext.getSize().y;
	float widthscale_gb = (float)WINDOW_WIDTH / temptext.getSize().x;

	std::pair <std::vector<std::vector<Obstacle>>, std::vector<sf::Texture>> obstacles_and_textures;
	obstacles_and_textures.second.push_back(temptext);

	if(!boss_time) {

	float obstacle_width = (WINDOW_WIDTH / 10) * .5;
	float obstacle_height = (WINDOW_HEIGHT / 12) * .5;
	float unit_width = WINDOW_WIDTH / 10;
	float unit_height = WINDOW_HEIGHT / 12;


	Texture cointext, spiketext, fueltext;

	int coin_num = rand() % 10 + 11;
	int RF_num = rand() % 5 + 10;
	int Spike_num = rand() % 10 + 10;

	std::vector<int> object_positions;
	std::vector<int> spike_positions;
	std::vector<int> coin_positions;
	std::vector<int> rocketfuel_positions;


	obstacles_and_textures.first.resize(3);
	obstacles_and_textures.second.resize(4);
	//auto first = object_positions.begin();

	obstacles_and_textures.second[0] = temptext;





	//gamebackground.setTexture(obstacles_and_textures.second[0], true);
	gamebackground.setScale(widthscale_gb, heightscale_gb);


	for(int i =0; i < Spike_num; i++) {
		int randnum = rand() % 100;
		auto tempit = std::find(object_positions.begin(), object_positions.end(), randnum);
		if(tempit != object_positions.end()) {
			i--;
		}
		else {
			object_positions.push_back(randnum);
			spike_positions.push_back(randnum);
		}

	}


	for(int i =0; i < coin_num; i++) {
		int randnum = rand() % 100;
		auto tempit = std::find(object_positions.begin(), object_positions.end(), randnum);
		if(tempit != object_positions.end()) {
			i--;
		}
		else {
			object_positions.push_back(randnum);
			coin_positions.push_back(randnum);
		}

	}


	for(int i =0; i < RF_num; i++) {
		int randnum = rand() % 100;
		auto tempit = std::find(object_positions.begin(), object_positions.end(), randnum);
		if(tempit != object_positions.end()) {
			i--;
		}
		else {
			object_positions.push_back(randnum);
			rocketfuel_positions.push_back(randnum);
		}

	}

	spiketext.loadFromFile("Sprites/spike_sprite.png");
	//spiketext.loadFromFile("Sprites/background.png");
	//obstacles_and_textures.second.push_back(spiketext);
	obstacles_and_textures.second[1] = spiketext;


		for(int i =0; i < Spike_num; i++) {
			int remainder = spike_positions[i];
			int quotient = 1;
			while(remainder >= 10) {
				quotient++;
				remainder -= 10;
			}
			Obstacle spike(obstacles_and_textures.second[1], sf::Vector2f(obstacle_width, obstacle_height), sf::Vector2f((float)unit_width*remainder,(float) unit_height *quotient) );
			obstacles_and_textures.first[0].push_back(spike);
		}


		cointext.loadFromFile("Sprites/coin_sprite.png");
		//cointext.loadFromFile("Sprites/background.png");
		//obstacles_and_textures.second.push_back(cointext);
		obstacles_and_textures.second[2] = cointext;

		for(int i =0; i < coin_num; i++) {
			int remainder = coin_positions[i];
			int quotient = 1;
			while(remainder >= 10) {
				quotient++;
				remainder -= 10;
			}
			Obstacle coin(obstacles_and_textures.second[2], sf::Vector2f(obstacle_width, obstacle_height), sf::Vector2f((float)unit_width*remainder, (float)unit_height *quotient) );
			obstacles_and_textures.first[1].push_back(coin);
		}

		fueltext.loadFromFile("Sprites/Metal.png");
		//fueltext.loadFromFile("Sprites/background.png");
		obstacles_and_textures.second[3] = fueltext;


		for(int i =0; i < RF_num; i++) {
			int remainder = rocketfuel_positions[i];
			int quotient = 1;
			while(remainder >= 10) {
				quotient++;
				remainder -= 10;
			}
			Obstacle rocketfuel(obstacles_and_textures.second[3], sf::Vector2f(obstacle_width, obstacle_height), sf::Vector2f((float)unit_width*remainder,(float) unit_height *quotient) );
			obstacles_and_textures.first[2].push_back(rocketfuel);
		}

	}



		return obstacles_and_textures;





	}



	void hurt_animation(Rocket& PlayerRocket, float& width_scale, float& height_scale, bool hurt) {
		//Texture temptexture;
		if(hurt) {

		if(PlayerRocket.num_type == 1) {
		temptexture.loadFromFile("Sprites/Rocket_1_flash.png");

		PlayerRocket.body.setTexture(&temptexture, true);
		PlayerRocket.body.setSize(sf::Vector2f(60,60));
		PlayerRocket.body.setScale(width_scale, height_scale);

		}
		}
		else if(PlayerRocket.num_type == 2) {
			temptexture.loadFromFile("Sprites/Rocket_2.png");

		PlayerRocket.body.setTexture(&temptexture, true);
		PlayerRocket.body.setSize(sf::Vector2f(60,60));
		PlayerRocket.body.setScale(width_scale, height_scale);
		}
		else {

		if(PlayerRocket.num_type == 1) {
		temptexture.loadFromFile("Sprites/Rocket_1.png");

		PlayerRocket.body.setTexture(&temptexture, true);
		PlayerRocket.body.setSize(sf::Vector2f(60,60));
		PlayerRocket.body.setScale(width_scale, height_scale);
		}

		else if(PlayerRocket.num_type == 2) {
			temptexture.loadFromFile("Sprites/Rocket_2.png");

		PlayerRocket.body.setTexture(&temptexture, true);
		PlayerRocket.body.setSize(sf::Vector2f(60,60));
		PlayerRocket.body.setScale(width_scale, height_scale);
		}

		}


		//return temptexture;

	}



	void create_boss(Enemy& Boss, int boss_num, int WINDOW_WIDTH, int WINDOW_HEIGHT) {
		Texture Bosst;

		if(boss_num == 1) {
			Bosst.loadFromFile("Sprites/Le_King_resized.png");
			//Boss.body.setTexture(&Bosst, true);
			Boss.Create_Enemy(Bosst, sf::Vector2f(WINDOW_WIDTH / 8, WINDOW_HEIGHT / 4.5), boss_num + 1, WINDOW_WIDTH, WINDOW_HEIGHT);
		}
		else if(boss_num == 2) {
		//Bosst.loadFromFile("Sprites/Le_King.png");
		}
		else if(boss_num == 3) {
		//Bosst.loadFromFile("Sprites/Le_King.png");
		}
		else if(boss_num == 4) {
		//Bosst.loadFromFile("Sprites/Le_King.png");
		}

	}


	/*void draw_boss(Enemy& Boss, RenderWindow& window, int boss_num, bool intro) {


	}*/



