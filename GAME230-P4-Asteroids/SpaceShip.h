#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameObject.h"

class SpaceShip : public GameObject {
public:
	SpaceShip(sf::Vector2f position, float speed, float angle, float radius);
	void update();
	void draw(sf::RenderWindow& window);
	void takeDamage();
	void reset();
};