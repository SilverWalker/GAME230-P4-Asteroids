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
	this->updateBuckets();

	if (asteroids.size() <= 0) {
		level++;
		player->reset();
		this->buildLevel(level);
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
	asteroids.clear();
	bullets.clear();
	player->reset();
	for (int i = 0; i < level+2; i++) {
		asteroids.push_back(new Asteroid({ WINDOW_WIDTH * (i + 3) * 0.1f, WINDOW_HEIGHT * 0.8f }, rand() % 100 + 100.0f * level, rand() % 360 - 180.0f, 2));
	}
}

void LevelHandler::updateBuckets()
{
	//Clear buckets
	for (int i = 0; i < this->COLUMNS * this->ROWS; i++) {
		this->gridBuckets.at(i).clear();
	}
	//Add game objects to buckets
	for (int i = 0; i < bullets.size(); i++) {
		addToBuckets(bullets.at(i));
	}
	for (int i = 0; i < asteroids.size(); i++) {
		addToBuckets(asteroids.at(i));
	}
	this->addToBuckets(player);
	//Detect collisions in each bucket
	for (int i = 0; i < gridBuckets.size(); i++) {
		if (gridBuckets[i].size() > 1) {
			detectCollisions(gridBuckets[i]);
		}
	}
	//Remove dead game object
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets.at(i)->isDead) {
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
	for (int i = 0; i < asteroids.size(); i++) {
		if (asteroids.at(i)->isDead) {
			delete asteroids[i];
			asteroids.erase(asteroids.begin() + i);
		}
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

void LevelHandler::detectCollisions(std::vector<GameObject*> bucket) {
	for (int i = 0; i < bucket.size()-1; i++) {
		for (int j = i + 1; j < bucket.size(); j++) {
			GameObject* obj1 = bucket.at(i);
			GameObject* obj2 = bucket.at(j);

			sf::Vector2f distanceVector = obj2->position - obj1->position;
			float distance = sqrt(pow(distanceVector.x, 2) + pow(distanceVector.y, 2));
			float radiusSum = obj1->radius + obj2->radius;
			if (distance <= radiusSum) {
				switch (obj1->type) {
				case 0: {
					if (obj2->type == 1) {
						player->takeDamage();
					}
				}break;
				case 1: {
					if (obj2->type == 0) {
						player->takeDamage();
					}
					if (obj2->type == 1) {
						float angle1 = atan2(distanceVector.y, distanceVector.x) * 180 / 3.14f;
						float angle2 = atan2(-distanceVector.y, -distanceVector.x) * 180 / 3.14f;
						obj2->angle = angle1;
						obj1->angle = angle2;
					}
					if (obj2->type == 2) {
						bucket.at(i)->isDead = true;
						bucket.at(j)->isDead = true;
					}
				}break;
				case 2: {
					if (obj2->type == 1) {
						bucket.at(i)->isDead = true;
						bucket.at(j)->isDead = true;
					}
				}break;
				}
			}
		}
	}
}