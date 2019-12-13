#include "Setting.h"

int WINDOW_WIDTH = 1000;
int WINDOW_HEIGHT = 800;

int currentState = 1; //1: Main menu, 2: In game, 3: Game over
int score = 0;
int life = 3;
int level = 1;

sf::Clock deltaClock;
sf::Time dt;
int frameCount = 0;

int asteroidSizes[] = { 10, 20, 40 };

SpaceShip* player;
std::vector<Asteroid*> asteroids;
std::vector<Bullet*> bullets;
LevelHandler* levelHandler;

sf::Texture spaceShipTexture;
sf::Texture asteroidTexture;

void loadAssets() {
	spaceShipTexture.loadFromFile("asset/texture/spaceShip.png");
	asteroidTexture.loadFromFile("asset/texture/asteroid.png");
}

void resetGame() {
	score = 0;
	life = 3;
	level = 1;
}