#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameObject {
public:
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;
	float angle;
	float radius;
	sf::CircleShape shape;
	sf::Color color;

	GameObject();
	void update();
	void draw(sf::RenderWindow& window);
};