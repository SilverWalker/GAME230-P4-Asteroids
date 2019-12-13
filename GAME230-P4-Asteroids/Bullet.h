#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameObject.h"

class Bullet : public GameObject {
public:
	int life;
	std::vector<sf::Vector2f> trails;
	sf::CircleShape trailShape;

	Bullet(sf::Vector2f position, float angle, int life, int colorId);
	void update();
	void draw(sf::RenderWindow& window);
};