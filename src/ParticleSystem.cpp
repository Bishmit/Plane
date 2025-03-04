#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(float vel_x, float vel_y, float movement)
    : velocity(vel_x, vel_y), movement(movement)
{
    if (!texture.loadFromFile("../resources/images/particle01.png")) {
        // Handle error if texture loading fails
    }
    sprite.setTexture(texture);
}


void ParticleSystem::update()
{
	sf::Vector2f position = sprite.getPosition();
	position.x += 1.5f; // Adjust the speed of movement
	sprite.setPosition(position);
}

void ParticleSystem::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

sf::FloatRect ParticleSystem::getbounds()
{
	return sprite.getGlobalBounds();
}

void ParticleSystem::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position); // Set the position of the sprite
}



