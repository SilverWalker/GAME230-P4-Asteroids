#include <iostream>
#include <cmath>
#include <vector>

#include "Setting.h"
#include "SpaceShip.h"

SpaceShip::SpaceShip(sf::Vector2f position, float speed, float angle, float radius) 
{
	this->speed = speed;
	this->angle = angle;
	this->radius = radius;
	this->position = position;
	this->color = sf::Color(255, 255, 255);
	this->type = 0;
	this->isDead = false;
	this->isInvisible = false;
	this->invisibleTime = 0;
	this->powerupShootType = 0;
	this->powerupShootTime = 0;

	this->shape.setRadius(this->radius);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setTexture(&spaceShipTexture);
}

void SpaceShip::update()
{
	if (this->speed > 0) {
		this->speed -= 0.10f;
	}
	else {
		this->speed = 0;
	}
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

	if (this->isInvisible) {
		this->invisibleTime--;
		if (this->invisibleTime <= 0) this->isInvisible = false;
	}

	if (this->powerupShootType > 0) {
		this->powerupShootTime--;
		if (this->powerupShootTime <= 0) this->powerupShootType = 0;
	}
}

void SpaceShip::draw(sf::RenderWindow& window)
{
	if (!this->isInvisible || (this->isInvisible && frameCount % 2 == 0)) {
		this->shape.setPosition(this->position.x, this->position.y);
		this->shape.setRotation(this->angle+90);
		this->shape.setFillColor(this->color);
		window.draw(this->shape);
	}
}

void SpaceShip::takeDamage()
{
	if (!this->isInvisible) {
		life--;
		playSound(4);
		for (int i = 0; i < 10; i++) {
			waves.push_back(new Wave(player->position.x + rand() % 100 - 50, player->position.y + rand() % 100 - 50, sf::Color::White));
		}
		this->reset();
		if (life <= 0) {
			life = 0;
			currentState = 3;
		}
	}
}

void SpaceShip::reset() {
	this->speed = 0.0f;
	this->angle = -90.0f;
	this->position = { WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f };
	this->isInvisible = true;
	this->invisibleTime = 1000;
	this->powerupShootType = 0;
	this->powerupShootTime = 0;
}