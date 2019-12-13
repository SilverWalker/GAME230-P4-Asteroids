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
#include "Powerup.h"

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
extern std::vector<Powerup*> powerups;
extern LevelHandler* levelHandler;

extern sf::Texture spaceShipTexture;
extern sf::Texture asteroidTexture;
extern sf::Texture powerupTextures[3];

extern sf::Color bulletColors[];
extern sf::Color powerupColors[];

extern std::vector<Wave*> waves;
extern std::vector<Particle*> particles;

extern sf::SoundBuffer thrustBuffer;
extern sf::SoundBuffer shootBuffer;
extern sf::SoundBuffer nextLevelBuffer;
extern sf::SoundBuffer destroyAsteroidBuffer;
extern sf::SoundBuffer destroySpaceShipBuffer;
extern sf::SoundBuffer powerupBuffer;
extern sf::SoundBuffer shootDeniedBuffer;
extern sf::Sound thrustSound;
extern sf::Sound ShootSound;
extern sf::Sound stageSound;
extern sf::Sound destroySound;

extern void loadAssets();
extern void resetGame();
extern void playSound(int soundId);
extern void stopSound(int soundId);