#include <iostream>
#include <cmath>
#include <vector>

#include "Setting.h"
#include "LevelHandler.h"

LevelHandler::LevelHandler()
{
	this->COLUMNS = 2;
	this->ROWS = 2;
	this->BUCKET_WIDTH = WINDOW_WIDTH / this->COLUMNS;
	this->BUCKET_HEIGHT = WINDOW_HEIGHT / this->ROWS;

	for (int i = 0; i < this->COLUMNS * this->ROWS; i++) {
		std::vector<GameObject*> vObj;
		this->gridBuckets.push_back(vObj);
	}
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
	this->checkCollision();
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
	this->clearBucket();
	for (int i = 0; i < bullets.size(); i++) {
		addToBuckets(bullets.at(i));
	}
	for (int i = 0; i < asteroids.size(); i++) {
		addToBuckets(asteroids.at(i));
	}
	this->addToBuckets(player);
}

void LevelHandler::clearBucket()
{
	for (int i = 0; i < this->COLUMNS * this->ROWS; i++) {
		this->gridBuckets.at(i).clear();
	}
}

void LevelHandler::addToBuckets(GameObject* obj)
{
	std::vector<int> atBuckets;
	atBuckets.push_back(this->getGrid(sf::Vector2f({ obj->position.x - obj->radius,obj->position.y - obj->radius })));
	atBuckets.push_back(this->getGrid(sf::Vector2f({ obj->position.x + obj->radius,obj->position.y - obj->radius })));
	atBuckets.push_back(this->getGrid(sf::Vector2f({ obj->position.x - obj->radius,obj->position.y + obj->radius })));
	atBuckets.push_back(this->getGrid(sf::Vector2f({ obj->position.x + obj->radius,obj->position.y + obj->radius })));
	std::sort(atBuckets.begin(), atBuckets.end());
	atBuckets.erase(std::unique(atBuckets.begin(), atBuckets.end()), atBuckets.end());

	for (int i = 0; i < atBuckets.size(); i++) {
		gridBuckets[atBuckets.at(i)].push_back(obj);
	}
	for (int i = 0; i < gridBuckets.size(); i++) {
		std::cout << i << ": ";
		std::cout << gridBuckets.at(i).size() << " ";
	}
	std::cout << std::endl;
}

int LevelHandler::getGrid(sf::Vector2f pos)
{
	int col = int(pos.x / this->BUCKET_WIDTH);
	if (col < 0) col = 0;
	if (col >= this->COLUMNS) col = this->COLUMNS - 1;
	int row = int(pos.y / this->BUCKET_HEIGHT);
	if (row < 0) row = 0;
	if (row >= this->ROWS) row = this->ROWS - 1;

	return row * this->COLUMNS + col;
}