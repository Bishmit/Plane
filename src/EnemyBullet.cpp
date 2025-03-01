#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::EnemyBullet(sf::Texture* Enemybulltex, float pos_x, float pos_y, float dir_x, float dir_y, float movementspeed, float size_x, float size_y)
{
	this->shape.setTexture(*Enemybulltex);
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementspeed = movementspeed;
	this->shape.setScale(size_x, size_y);
}

EnemyBullet::~EnemyBullet()
{
}

const sf::FloatRect EnemyBullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}


void EnemyBullet::update(sf::RenderTarget* target) {
	this->shape.move(this->movementspeed * this->direction);
}

void EnemyBullet::render(sf::RenderTarget* target) {
	target->draw(this->shape);
}