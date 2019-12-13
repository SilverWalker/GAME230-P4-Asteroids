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
	frameCount++;
	for (int i = 0; i < bullets.size(); i++) {
		bullets.at(i)->update();
		if (bullets.at(i)->life <= 0) {
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids.at(i)->update();
	}
	for (int i = 0; i < powerups.size(); i++) {
		powerups.at(i)->update();
	}
	player->update();
	for (int i = 0; i < waves.size(); i++) {
		waves.at(i)->update();
	}
	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->update();
	}
	this->updateBuckets();

	if (asteroids.size() <= 0) {
		level++;
		playSound(2);
		player->reset();
		this->buildLevel(level);
	}
}

void LevelHandler::render(sf::RenderWindow& window)
{
	for (int i = 0; i < powerups.size(); i++) {
		powerups.at(i)->draw(window);
	}
	for (int i = 0; i < bullets.size(); i++) {
		bullets.at(i)->draw(window);
	}
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids.at(i)->draw(window);
	}
	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->draw(window);
	}
	player->draw(window);
	for (int i = 0; i < waves.size(); i++) {
		waves.at(i)->draw(window);
	}
}

void LevelHandler::buildLevel(int level)
{
	asteroids.clear();
	bullets.clear();
	powerups.clear();
	waves.clear();
	particles.clear();
	player->reset();
	for (int i = 0; i < level+2; i++) {
		int distance = rand() % 400 + 100;
		float angle = (i * 360 / (level + 2));
		float posX = WINDOW_WIDTH / 2 + distance * cosf(angle * 3.14f / 180);
		float posY = WINDOW_HEIGHT / 2 + distance * sinf(angle * 3.14f / 180);
		asteroids.push_back(new Asteroid({ posX, posY }, rand() % 100 + 50.0f * level, rand() % 360 - 180.0f, 2));
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
	for (int i = 0; i < powerups.size(); i++) {
		addToBuckets(powerups.at(i));
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
	for (int i = 0; i < powerups.size(); i++) {
		if (powerups.at(i)->isDead) {
			delete powerups[i];
			powerups.erase(powerups.begin() + i);
		}
	}
	for (int i = 0; i < waves.size(); i++) {
		if (waves.at(i)->isDead) {
			delete waves[i];
			waves.erase(waves.begin() + i);
		}
	}
	for (int i = 0; i < particles.size(); i++) {
		if (particles.at(i)->isDead) {
			delete particles[i];
			particles.erase(particles.begin() + i);
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
					if (obj2->type == 3) {
						playSound(5);
						bucket.at(j)->isDead = true;
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
						waves.push_back(new Wave(obj1->position.x, obj1->position.y, obj2->color));
						playSound(3);
						bucket.at(i)->isDead = true;
						bucket.at(j)->isDead = true;
					}
				}break;
				case 2: {
					if (obj2->type == 1) {
						waves.push_back(new Wave(obj2->position.x, obj2->position.y, obj1->color));
						playSound(3);
						bucket.at(i)->isDead = true;
						bucket.at(j)->isDead = true;
					}
				}break;
				case 3: {
					if (obj2->type == 0) {
						playSound(5);
						bucket.at(i)->isDead = true;
					}
				}break;
				}
			}
		}
	}
}