#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameObject.h"

class Asteroid : public GameObject {
public:
	int sizeLevel; //0: Small, 1: Medium, 2: Large

	Asteroid(sf::Vector2f position, float speed, float angle, int sizeLevel);
	~Asteroid();
	void update();
	void draw(sf::RenderWindow& window);
};