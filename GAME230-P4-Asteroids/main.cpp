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
#include "Asteroid.h"
#include "Bullet.h"
#include "LevelHandler.h"
#include "Wave.h"
#include "Particle.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids");
	loadAssets();
	player = new SpaceShip({ WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f }, 0.0f, -90.0f, 20.0f);
	Ui ui;
	levelHandler = new LevelHandler();


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
						resetGame();
						levelHandler->buildLevel(1);
						currentState = 2;
					}
					if (mousePos.x > WINDOW_WIDTH * 0.5 - 100 && mousePos.x < WINDOW_WIDTH * 0.5 + 100
						&& mousePos.y> WINDOW_HEIGHT * 0.78 - 25 && mousePos.y < WINDOW_HEIGHT * 0.78 + 25) {
						window.close();
					}
				}break;
				case 2: {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						if (bullets.size() < 5 && player->powerupShootType == 0) {
							bullets.push_back(new Bullet({ player->position.x, player->position.y }, player->angle, 2000, 0));
							playSound(1);
						}
						else if (bullets.size() < 15 && player->powerupShootType == 2) {
							bullets.push_back(new Bullet({ player->position.x, player->position.y }, player->angle + 30.0f, 200, 2));
							bullets.push_back(new Bullet({ player->position.x, player->position.y }, player->angle, 200, 2));
							bullets.push_back(new Bullet({ player->position.x, player->position.y }, player->angle - 30.0f, 200, 2));
							playSound(1);
						}
						else {
							playSound(6);
						}
					}
				}break;
				case 3: {
					if (mousePos.x > WINDOW_WIDTH * 0.5 - 125 && mousePos.x < WINDOW_WIDTH * 0.5 + 125
						&& mousePos.y> WINDOW_HEIGHT * 0.68 - 25 && mousePos.y < WINDOW_HEIGHT * 0.68 + 25) {
						currentState = 1;
					}
				}break;
				}
			}
			if (event.type == sf::Event::EventType::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Right) stopSound(0);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && currentState == 2) {
			if (player->speed < 500.5f) {
				player->speed += 0.1f * (6 - int(player->speed / 100));
			}
			if (frameCount % 60 == 0) playSound(0);
			particles.push_back(new Particle(player->position, 300.0f, player->angle - 180.0f + sin(frameCount) * 20));
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == 2 && player->powerupShootType==1 && frameCount % 10==0) {
			bullets.push_back(new Bullet({ player->position.x, player->position.y }, player->angle, 100, 1));
			playSound(1);
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		float mouseDistance = sqrt(pow(mousePos.x - player->position.x, 2) + pow(mousePos.y - player->position.y, 2));
		if (mouseDistance < 10.0f) {
			player->speed -= 10.0f - mouseDistance;
		}
		float mouseAngle = atan2(mousePos.y - player->position.y, mousePos.x - player->position.x) * 180 / 3.14f;
		player->angle = mouseAngle;

		window.clear();
		ui.drawBackground(window);
		switch (currentState) {
			case 1: {
				ui.drawMainMenu(window);
			}break;
			case 2: {
				levelHandler->update();
				levelHandler->render(window);
				ui.update();
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