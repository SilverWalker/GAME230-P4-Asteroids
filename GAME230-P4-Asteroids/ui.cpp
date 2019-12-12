#include <iostream>
#include <string>

#include "Setting.h"
#include "Ui.h"

Ui::Ui()
{
	this->font.loadFromFile("asset/font/JustMyType-KePl.ttf");

	//1: Main menu
	this->titleText.setFont(this->font);
	this->titleText.setString("Asteroids");
	this->titleText.setCharacterSize(WINDOW_WIDTH / 12);
	this->titleText.setFillColor(sf::Color::White);
	sf::FloatRect titleBounds = this->titleText.getLocalBounds();
	this->titleText.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.5 - titleBounds.width / 2, WINDOW_HEIGHT * 0.3));

	this->startText.setFont(this->font);
	this->startText.setString("Start");
	this->startText.setCharacterSize(WINDOW_WIDTH / 24);
	this->startText.setFillColor(sf::Color::White);
	sf::FloatRect startBounds = this->startText.getLocalBounds();
	this->startText.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.5 - startBounds.width / 2, WINDOW_HEIGHT * 0.65));

	this->startBtn.setSize({ 200,50 });
	this->startBtn.setFillColor(sf::Color::Transparent);
	this->startBtn.setOutlineColor(sf::Color::White);
	this->startBtn.setOutlineThickness(3);
	this->startBtn.setOrigin(100, 25);
	this->startBtn.setPosition(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.68);

	this->exitText.setFont(this->font);
	this->exitText.setString("Exit");
	this->exitText.setCharacterSize(WINDOW_WIDTH / 24);
	this->exitText.setFillColor(sf::Color::White);
	sf::FloatRect exitBounds = this->exitText.getLocalBounds();
	this->exitText.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.5 - exitBounds.width / 2, WINDOW_HEIGHT * 0.75));

	this->exitBtn.setSize({ 200,50 });
	this->exitBtn.setFillColor(sf::Color::Transparent);
	this->exitBtn.setOutlineColor(sf::Color::White);
	this->exitBtn.setOutlineThickness(3);
	this->exitBtn.setOrigin(100, 25);
	this->exitBtn.setPosition(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.78);

	//2: In game
	this->scoreText.setFont(this->font);
	this->scoreText.setString("Score: " + std::to_string(score));
	this->scoreText.setCharacterSize(WINDOW_WIDTH / 36);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.01));

	this->lifeText.setFont(this->font);
	this->lifeText.setString("Life: " + std::to_string(life));
	this->lifeText.setCharacterSize(WINDOW_WIDTH / 36);
	this->lifeText.setFillColor(sf::Color::White);
	this->lifeText.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.01));

	this->levelText.setFont(this->font);
	this->levelText.setString("Level: " + std::to_string(level));
	this->levelText.setCharacterSize(WINDOW_WIDTH / 36);
	this->levelText.setFillColor(sf::Color::White);
	this->levelText.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.6, WINDOW_HEIGHT * 0.01));


	//3: Game over
	this->gameOverText.setFont(this->font);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setCharacterSize(WINDOW_WIDTH / 12);
	this->gameOverText.setFillColor(sf::Color::White);
	sf::FloatRect gameOverBounds = this->gameOverText.getLocalBounds();
	this->gameOverText.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.5 - gameOverBounds.width / 2, WINDOW_HEIGHT * 0.4));

	this->backToMenuText.setFont(this->font);
	this->backToMenuText.setString("Back to main menu");
	this->backToMenuText.setCharacterSize(WINDOW_WIDTH / 24);
	this->backToMenuText.setFillColor(sf::Color::White);
	sf::FloatRect backToMenuBounds = this->backToMenuText.getLocalBounds();
	this->backToMenuText.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.5 - backToMenuBounds.width / 2, WINDOW_HEIGHT * 0.65));

	this->backToMenutBtn.setSize({ 250,50 });
	this->backToMenutBtn.setFillColor(sf::Color::Transparent);
	this->backToMenutBtn.setOutlineColor(sf::Color::White);
	this->backToMenutBtn.setOutlineThickness(3);
	this->backToMenutBtn.setOrigin(125, 25);
	this->backToMenutBtn.setPosition(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.68);
}

void Ui::update()
{
}

void Ui::drawMainMenu(sf::RenderWindow& window)
{
	window.draw(this->titleText);
	window.draw(this->startBtn);
	window.draw(this->startText);
	window.draw(this->exitBtn);
	window.draw(this->exitText);
}

void Ui::drawInGameInfo(sf::RenderWindow& window)
{
	window.draw(this->scoreText);
	window.draw(this->lifeText);
	window.draw(this->levelText);
}

void Ui::drawGameOver(sf::RenderWindow& window)
{
	window.draw(this->gameOverText);
	window.draw(this->backToMenutBtn);
	window.draw(this->backToMenuText);
}