#include <iostream>
#include <cmath>
#include <vector>

#include "Setting.h"
#include "Asteroid.h"

Asteroid::Asteroid(sf::Vector2f position, float speed, float angle, int sizeLevel)
{
	this->speed = speed;
	this->angle = angle;
	this->sizeLevel = sizeLevel;
	this->radius = asteroidSizes[sizeLevel];
	this->position = position;
	this->color = sf::Color(255, 255, 0);
	this->type = 1;
	this->isDead = false;

	this->shape.setRadius(this->radius);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setTexture(&asteroidTexture);
}

Asteroid::~Asteroid()
{
	score += 40 + 10 * level;
	if (this->sizeLevel > 0) {
		asteroids.push_back(new Asteroid(this->position, rand() % 100 + 50.0f * level, this->angle - 90, this->sizeLevel - 1));
		asteroids.push_back(new Asteroid(this->position, rand() % 100 + 50.0f * level, this->angle + 90, this->sizeLevel - 1));
		int powerupRnd = int(rand() % 100);
		if (powerupRnd < 20) {
			powerups.push_back(new Powerup(this->position, int(rand() % 3)));
		}
	}
}

void Asteroid::update()
{
	this->velocity.x = this->speed * cosf(this->angle * 3.14f / 180);
	this->velocity.y = this->speed * sinf(this->angle * 3.14f / 180);
	this->position.x += this->velocity.x * dt.asSeconds();
	this->position.y += this->velocity.y * dt.asSeconds();
	if (this->position.x < -this->radius) {
		this->position.x = WINDOW_WIDTH + this->radius;
	}
	if (this->position.x > WINDOW_WIDTH + this->radius) {
		this->position.x = -this->radius;
	}
	if (this->position.y < -this->radius) {
		this->position.y = WINDOW_HEIGHT + this->radius;
	}
	if (this->position.y > WINDOW_HEIGHT + this->radius) {
		this->position.y = -this->radius;
	}
}

void Asteroid::draw(sf::RenderWindow& window)
{
	this->shape.setPosition(this->position.x, this->position.y);
	this->shape.setRotation(this->angle + 90 + frameCount*0.01);
	this->shape.setFillColor(this->color);
	window.draw(this->shape);
}