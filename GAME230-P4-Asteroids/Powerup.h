#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameObject.h"

class Powerup : public GameObject {
public:
	int upType; //0: Temporary invincibility, 1: Rapid fire, 2: Spread shot

	Powerup(sf::Vector2f position, int upType);
	~Powerup();
	void update();
	void draw(sf::RenderWindow& window);
};