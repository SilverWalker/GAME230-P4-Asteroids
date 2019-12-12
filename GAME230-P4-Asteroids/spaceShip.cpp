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

	this->shape.setRadius(this->radius);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setTexture(&spaceShipTexture);
}

void SpaceShip::update()
{
}

void SpaceShip::draw(sf::RenderWindow& window)
{
	this->shape.setPosition(this->position.x, this->position.y);
	this->shape.setFillColor(this->color);
	window.draw(this->shape);
}