#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameObject.h"

class SpaceShip : public GameObject {
public:
	bool isInvisible;
	int invisibleTime;
	int powerupShootType; //0: Nothing, 1: Rapid Fire, 2: Spread shot
	int powerupShootTime;

	SpaceShip(sf::Vector2f position, float speed, float angle, float radius);
	void update();
	void draw(sf::RenderWindow& window);
	void takeDamage();
	void reset();
};