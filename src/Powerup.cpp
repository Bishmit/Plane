#include "Powerup.h"

Powerup::Powerup(sf::Texture* hptex)
{
	hp.setTexture(*hptex); 
	hp.setScale(sf::Vector2f(0.5f, 0.5f));
}

void Powerup::update()
{
	// here we move the powerup thing
	sf::Vector2f position = hp.getPosition();
	position.y += 2.5f; 
	hp.setPosition(position);
}

void Powerup::render(sf::RenderWindow* target)
{
	target->draw(hp); 
}

const sf::FloatRect Powerup::getBounds() const {
	return hp.getGlobalBounds();
}

void Powerup::setPosition(const sf::Vector2f& position) {
	hp.setPosition(position); // Set the position of the sprite
}

const sf::Vector2f& Powerup::getPos() const
{
	return hp.getPosition();
}



