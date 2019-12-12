#include "Setting.h"

int WINDOW_WIDTH = 1000;
int WINDOW_HEIGHT = 800;

int currentState = 3; //1: Main menu, 2: In game, 3: Game over
int score = 0;
int life = 3;
bool isGameOver = false;
int level = 1;

sf::Clock deltaClock;
sf::Time dt;
int frameCount = 0;

void resetGame() {
	score = 0;
	life = 3;
	level = 1;
	isGameOver = false;
}