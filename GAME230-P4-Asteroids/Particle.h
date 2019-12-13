#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Particle {
public:
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;
	float angle;
	float radius;
	sf::CircleShape shape;
	sf::Color color;
	int life;
	bool isDead;

	Particle(sf::Vector2f position, float speed, float angle);
	void update();
	void draw(sf::RenderWindow& window);
};