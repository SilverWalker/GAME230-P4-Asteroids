#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Ui {
public:
	sf::Font font;

	//1: Main menu
	sf::Text titleText;
	sf::Text startText;
	sf::RectangleShape startBtn;
	sf::Text exitText;
	sf::RectangleShape exitBtn;
	//2: In game
	sf::Text scoreText;
	sf::Text lifeText;
	sf::Text levelText;
	//3: Game over
	sf::Text gameOverText;
	sf::Text backToMenuText;
	sf::RectangleShape backToMenutBtn;

	Ui();
	void update();
	void drawMainMenu(sf::RenderWindow& window);
	void drawInGameInfo(sf::RenderWindow& window);
	void drawGameOver(sf::RenderWindow& window);
};