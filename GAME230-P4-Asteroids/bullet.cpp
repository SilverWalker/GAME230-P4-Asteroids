#include <iostream>
#include <cmath>
#include <vector>

#include "Setting.h"
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, float angle)
{
	this->speed = 500.0f;
	this->angle = angle;
	this->radius = 5;
	this->position = position;
	this->color = sf::Color(69, 190, 255);
	this->life = 3000;
	this->type = 2;
	this->isDead = false;

	this->shape.setRadius(this->radius);
	this->shape.setOrigin(this->radius, this->radius);

	this->trails.clear();
	for (int i = 0; i < 10; i++) {
		this->trails.push_back(sf::Vector2f(this->position.x, this->position.y));
	}
}

void Bullet::update()
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
	this->life--;

	if (frameCount % 10 == 0) {
		this->trails.erase(this->trails.begin());
		this->trails.push_back(sf::Vector2f(this->position.x, this->position.y));
	}
}

void Bullet::draw(sf::RenderWindow& window)
{
	this->shape.setPosition(this->position.x, this->position.y);
	this->shape.setFillColor(this->color);

	for (int i = 0; i < this->trails.size(); i++) {
		this->trailShape.setRadius(this->radius * i / this->trails.size());
		this->trailShape.setOrigin(this->radius * i / this->trails.size(), this->radius * i / this->trails.size());
		this->trailShape.setPosition(this->trails.at(i));
		sf::Color trailColor = this->color;
		trailColor.a = 150-i*10;
		this->trailShape.setFillColor(trailColor);
		window.draw(this->trailShape);
	}

	window.draw(this->shape);
}