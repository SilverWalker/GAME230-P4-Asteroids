#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Wave {
public:
	sf::Vector2f position;
	float radius;
	sf::CircleShape circleWave;
	sf::Color color;
	int life;
	bool isDead;

	Wave(float pX, float pY, sf::Color color);
	void update();
	void draw(sf::RenderWindow& window);
};