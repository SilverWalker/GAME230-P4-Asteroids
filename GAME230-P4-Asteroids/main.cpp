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

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids");
	Ui ui;

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

		window.clear();
		switch (currentState) {
			case 1: {
				ui.drawMainMenu(window);
			}break;
			case 2: {
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
