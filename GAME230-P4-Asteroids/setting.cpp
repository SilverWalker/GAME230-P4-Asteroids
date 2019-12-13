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

std::vector<Wave*> waves;
std::vector<Particle*> particles;

sf::SoundBuffer thrustBuffer;
sf::SoundBuffer shootBuffer;
sf::SoundBuffer nextLevelBuffer;
sf::SoundBuffer destroyAsteroidBuffer;
sf::SoundBuffer destroySpaceShipBuffer;
sf::Sound thrustSound;
sf::Sound shootSound;
sf::Sound stageSound;
sf::Sound destroySound;

void loadAssets() {
	spaceShipTexture.loadFromFile("asset/texture/spaceShip.png");
	asteroidTexture.loadFromFile("asset/texture/asteroid.png");

	thrustBuffer.loadFromFile("asset/sound/thrust.wav");
	shootBuffer.loadFromFile("asset/sound/shoot.wav");
	nextLevelBuffer.loadFromFile("asset/sound/nextLevel.wav");
	destroyAsteroidBuffer.loadFromFile("asset/sound/destroyAsteroid.wav");
	destroySpaceShipBuffer.loadFromFile("asset/sound/destroySpaceShip.wav");
}

void resetGame() {
	score = 0;
	life = 3;
	level = 1;
}

void playSound(int soundId) {
	switch (soundId) {
	case 0:
		thrustSound.setBuffer(thrustBuffer);
		thrustSound.setVolume((250 + player->speed / 2) / 5.0f);
		thrustSound.play();
		break;
	case 1:
		shootSound.setBuffer(shootBuffer);
		shootSound.play();
		break;
	case 2:
		stageSound.setBuffer(nextLevelBuffer);
		stageSound.play();
		break;
	case 3:
		destroySound.setBuffer(destroyAsteroidBuffer);
		destroySound.play();
		break;
	case 4:
		destroySound.setBuffer(destroySpaceShipBuffer);
		destroySound.play();
		break;
	}
}

void stopSound(int soundId) {
	switch (soundId) {
	case 0:
		thrustSound.stop();
		break;
	}
}