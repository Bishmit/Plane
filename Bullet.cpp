#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* bulltex, float pos_x, float pos_y, float dir_x, float dir_y, float movementspeed,float size_x, float size_y)
{
	this->shape.setTexture(*bulltex); 
	this->shape.setPosition(pos_x, pos_y); 
	this->direction.x = dir_x; 
	this->direction.y = dir_y; 
	this->movementspeed = movementspeed; 
	this->shape.setScale(size_x, size_y); 
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds(); 
}


void Bullet::update(sf::RenderTarget* target) {
	this->shape.move(this->movementspeed * this->direction); 
}

void Bullet::render(sf::RenderTarget * target) {
	target->draw(this->shape); 
}