#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameObject.h"

class LevelHandler {
public:
	LevelHandler();
	void update();
	void render(sf::RenderWindow& window);
	void buildLevel(int level);
	void checkCollision();
};