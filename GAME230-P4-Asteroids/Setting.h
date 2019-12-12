#pragma once
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Ui.h"
#include "GameObject.h"
#include "SpaceShip.h"
#include "Asteroid.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int currentState;
extern int score;
extern int life;
extern bool isGameOver;
extern int level;

extern sf::Clock deltaClock;
extern sf::Time dt;
extern int frameCount;

extern int asteroidSizes[];

extern SpaceShip* player;
extern std::vector<Asteroid*> asteroids;

extern sf::Texture spaceShipTexture;

extern void loadAssets();
extern void resetGame();