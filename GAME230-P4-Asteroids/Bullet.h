#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameObject.h"

class Bullet : public GameObject {
public:
	int life;

	Bullet(sf::Vector2f position, float angle);
	void update();
	void draw(sf::RenderWindow& window);
};