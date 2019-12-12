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
	this->velocity.x = this->speed * cosf(this->angle * 3.14f / 180);
	this->velocity.y = this->speed * sinf(this->angle * 3.14f / 180);
	this->position.x += this->velocity.x * dt.asSeconds();
	this->position.y += this->velocity.y * dt.asSeconds();
	if (this->speed > 0) {
		this->speed -= 0.02f;
	}
	else {
		this->speed = 0;
	}
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

void SpaceShip::draw(sf::RenderWindow& window)
{
	this->shape.setPosition(this->position.x, this->position.y);
	this->shape.setRotation(this->angle+90);
	this->shape.setFillColor(this->color);
	window.draw(this->shape);
}