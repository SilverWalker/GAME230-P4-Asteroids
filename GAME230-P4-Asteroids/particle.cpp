#include <iostream>
#include "Setting.h"
#include "Particle.h"

Particle::Particle(sf::Vector2f position, float speed, float angle)
{
	this->position = position;
	this->speed = speed;
	this->angle = angle;
	this->life = 200;
	this->radius = 2;
	this->isDead = false;
	this->color = sf::Color(255, this->life, 0);

	shape.setRadius({ this->radius });
	shape.setOrigin(this->radius, this->radius);
}

void Particle::update()
{
	this->life--;
	if (this->life <= 0) this->isDead = true;
	this->color = sf::Color(255, this->life, 0);
	int alpha = (player->speed / 2) - (200 - this->life) / 2;
	this->color.a = alpha > 255 ? 255 : alpha < 0 ? 0 : alpha;

	this->speed*=1.01;
	this->velocity.x = this->speed * cosf(this->angle * 3.14f / 180);
	this->velocity.y = this->speed * sinf(this->angle * 3.14f / 180);
	this->position.x += this->velocity.x * dt.asSeconds();
	this->position.y += this->velocity.y * dt.asSeconds();
}

void Particle::draw(sf::RenderWindow& window)
{
	shape.setFillColor(this->color);
	shape.setPosition(this->position.x, this->position.y);
	window.draw(shape);
}