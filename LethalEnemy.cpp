#include "LethalEnemy.h"

LethalEnemy::LethalEnemy()
{
	if (!tex.loadFromFile("Enemy/extra enemy/Enemy2.png")) {
		std::cout << "Error" << "\n";
	}
	sprite.setTexture(tex);
	sprite.setPosition(500.f, -100.f);
	sprite.setScale(sf::Vector2f(0.3f,0.3f));
}

void LethalEnemy::update()
{
	sf::Vector2f position = sprite.getPosition();
	position.y += 4.5f;
	sprite.setPosition(position);
}

void LethalEnemy::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}
