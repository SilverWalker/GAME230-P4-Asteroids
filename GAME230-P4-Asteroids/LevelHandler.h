#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameObject.h"

class LevelHandler {
public:
	int COLUMNS;
	int ROWS;
	float BUCKET_WIDTH;
	float BUCKET_HEIGHT;
	std::vector<std::vector<GameObject*>> gridBuckets;

	LevelHandler();
	void update();
	void render(sf::RenderWindow& window);
	void buildLevel(int level);
	void updateBuckets();
	void addToBuckets(GameObject* obj);
	int getGrid(sf::Vector2f pos);
	void detectCollisions(std::vector<GameObject*> bucket);
};