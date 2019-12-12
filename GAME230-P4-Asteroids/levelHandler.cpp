#include <iostream>
#include <cmath>
#include <vector>

#include "Setting.h"
#include "LevelHandler.h"

LevelHandler::LevelHandler()
{
}

void LevelHandler::update()
{
	for (int i = 0; i < bullets.size(); i++) {
		bullets.at(i)->update();
		if (bullets.at(i)->life <= 0) {
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
	player->update();
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids.at(i)->update();
	}
}

void LevelHandler::render(sf::RenderWindow& window)
{
	for (int i = 0; i < bullets.size(); i++) {
		bullets.at(i)->draw(window);
	}
	player->draw(window);
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids.at(i)->draw(window);
	}
}

void LevelHandler::buildLevel(int level)
{
	for (int i = 0; i < level+2; i++) {
		asteroids.push_back(new Asteroid({ WINDOW_WIDTH * (i + 3) * 0.1f, WINDOW_HEIGHT * (i+3)*0.1f }, rand() % 20 + 20.0f, rand() % 360 - 180.0f, i % 3));
	}
}

void LevelHandler::checkCollision()
{
	
}