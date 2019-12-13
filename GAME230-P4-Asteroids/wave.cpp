#include <iostream>
#include "Setting.h"
#include "Wave.h"

Wave::Wave(float pX, float pY, sf::Color color)
{
	this->position.x = pX;
	this->position.y = pY;
	this->life = 200;
	this->color = color;
	this->color.a = this->life * 0.75 + 105;
	this->radius = (200.0f - this->life) / 4;
	this->isDead = false;
}

void Wave::update()
{
	this->life--;
	if (this->life <= 0) this->isDead = true;
	this->radius = (200.0f - this->life) / 4;
	this->color.a = this->life * 0.75 + 105;
}

void Wave::draw(sf::RenderWindow& window)
{
	circleWave.setRadius({ this->radius });
	circleWave.setOrigin(this->radius, this->radius);
	circleWave.setPosition(this->position.x, this->position.y);
	circleWave.setFillColor(sf::Color::Transparent);
	circleWave.setOutlineColor(this->color);
	circleWave.setOutlineThickness(3);
	window.draw(circleWave);
}