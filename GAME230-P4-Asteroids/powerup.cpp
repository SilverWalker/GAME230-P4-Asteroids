#include <iostream>
#include <cmath>
#include <vector>

#include "Setting.h"
#include "Powerup.h"

Powerup::Powerup(sf::Vector2f position, int upType)
{
	this->radius = 20;
	this->position = position;
	this->color = powerupColors[upType];
	this->upType = upType;
	this->type = 3;
	this->isDead = false;

	this->shape.setRadius(this->radius);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setPosition(this->position.x, this->position.y);
	this->shape.setTexture(&powerupTextures[this->upType]);
	this->shape.setFillColor(this->color);
}

Powerup::~Powerup()
{
	switch (this->upType) {
	case 0:
		player->isInvisible = true;
		player->invisibleTime = 1000;
		break;
	case 1:
		player->powerupShootType = 1;
		player->powerupShootTime = 500;
		break;
	case 2:
		player->powerupShootType = 2;
		player->powerupShootTime = 1000;
		break;
	}
}

void Powerup::update()
{
}

void Powerup::draw(sf::RenderWindow& window)
{
	window.draw(this->shape);
}