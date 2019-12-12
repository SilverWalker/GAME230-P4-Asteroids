#include <iostream>
#include <stdlib.h> 
#include <time.h> 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "Setting.h"
#include "Ui.h"
#include "GameObject.h"
#include "SpaceShip.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids");
	loadAssets();
	player = new SpaceShip({ WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f }, 0.0f, -90.0f, 20.0f);
	Ui ui;
	for (int i = 0; i < 10; i++) {
		asteroids.push_back(new Asteroid({ WINDOW_WIDTH * i * 0.1f, WINDOW_HEIGHT * i * 0.1f }, rand()%20+20.0f, rand()%360-180.0f, i%3));
	}


	srand(time(NULL));
	while (window.isOpen())
	{
		dt = deltaClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::EventType::KeyPressed) {
				//Press Esc to go back to main menu
				if (event.key.code == sf::Keyboard::Escape && currentState==2) {
					currentState = 1;
				}
			}
			if (event.type == sf::Event::EventType::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				switch (currentState) {
				case 1: {
					if (mousePos.x > WINDOW_WIDTH * 0.5 - 100 && mousePos.x < WINDOW_WIDTH * 0.5 + 100
					&& mousePos.y> WINDOW_HEIGHT * 0.68 - 25 && mousePos.y < WINDOW_HEIGHT * 0.68 + 25) {
						currentState = 2;
					}
					if (mousePos.x > WINDOW_WIDTH * 0.5 - 100 && mousePos.x < WINDOW_WIDTH * 0.5 + 100
						&& mousePos.y> WINDOW_HEIGHT * 0.78 - 25 && mousePos.y < WINDOW_HEIGHT * 0.78 + 25) {
						window.close();
					}
				}break;
				case 2: {
				}break;
				case 3: {
					if (mousePos.x > WINDOW_WIDTH * 0.5 - 125 && mousePos.x < WINDOW_WIDTH * 0.5 + 125
						&& mousePos.y> WINDOW_HEIGHT * 0.68 - 25 && mousePos.y < WINDOW_HEIGHT * 0.68 + 25) {
						currentState = 1;
					}
				}break;
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && currentState == 2) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			float mouseAngle = atan2(mousePos.y - player->position.y, mousePos.x - player->position.x) * 180 / 3.14f;
			float mouseDistance = sqrt(pow(mousePos.x - player->position.x, 2) + pow(mousePos.y - player->position.y, 2));
			std::cout << mouseAngle << " " << player->speed << std::endl;
			/*if (int(player->angle + 360) % 360 > int(mouseAngle + 360) % 360) {
				player->angle -= 1;
			}
			else if (int(player->angle + 360) % 360 < int(mouseAngle + 360) % 360) {
				player->angle += 1;
			}*/
			player->angle = mouseAngle;
			if (player->speed < 300.0f) {
				player->speed += 0.05f;
			}
		}

		window.clear();
		switch (currentState) {
			case 1: {
				ui.drawMainMenu(window);
			}break;
			case 2: {
				player->update();
				player->draw(window);
				for (int i = 0; i < asteroids.size(); i++) {
					asteroids.at(i)->update();
					asteroids.at(i)->draw(window);
				}
				ui.drawInGameInfo(window);
			}break;
			case 3: {
				ui.drawInGameInfo(window);
				ui.drawGameOver(window);
			}break;
		}
		window.display();
	}

	return 0;
}
