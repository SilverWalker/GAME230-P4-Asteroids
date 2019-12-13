#pragma once
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Ui.h"
#include "GameObject.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "LevelHandler.h"
#include "Wave.h"
#include "Particle.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int currentState;
extern int score;
extern int life;
extern int level;

extern sf::Clock deltaClock;
extern sf::Time dt;
extern int frameCount;

extern int asteroidSizes[];

extern SpaceShip* player;
extern std::vector<Asteroid*> asteroids;
extern std::vector<Bullet*> bullets;
extern LevelHandler* levelHandler;

extern sf::Texture spaceShipTexture;
extern sf::Texture asteroidTexture;

extern std::vector<Wave*> waves;
extern std::vector<Particle*> particles;

extern void loadAssets();
extern void resetGame();