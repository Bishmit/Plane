#include "BossEnemy.h"

BossEnemy::BossEnemy()
{
	if (!tex.loadFromFile("Enemy/extra enemy/Enemy5.png")) {
		std::cout << "Error" << "\n"; 
	}
	sprite.setTexture(tex); 
	sprite.setPosition(100.f, -100.f); 
	sprite.setScale(sf::Vector2f(0.3f, 0.3f));
}

void BossEnemy::update()
{
	// boss enemy behaviour
	// for now lets just set it as usual 
	sf::Vector2f position = sprite.getPosition();
	position.y += 4.5f; // Adjust the speed of movement
	sprite.setPosition(position);
}

void BossEnemy::draw(sf::RenderWindow* window)
{
	window->draw(sprite); 
}

