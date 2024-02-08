#include "Player.h"

Player::Player(float x, float y) {
    this->sprite.setPosition(x, y); 
    initVariable();
    initsprite();
}

void Player::initVariable() {
    // Initialization of variables
    this->speed = 5; 
}

void Player::initsprite() {
    if (!tex.loadFromFile("Eagle.png")) {
        // error
    }
    sprite.setTexture(tex); 
}
void Player::updateWallCollision(const sf::RenderTarget* target)
{

    // Ensure the player stays within the left boundary
    if (this->sprite.getGlobalBounds().left <= 0.f) {
        this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
    }

    // Ensure the player stays within the right boundary
    if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x) {
        this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
    }

    // Ensure the player stays within the top boundary
    if (this->sprite.getGlobalBounds().top <= 0.f) {
        this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
    }

}


void Player::update(const sf::RenderTarget *target) {
    // Update game logic i mean moving the sprite/player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->sprite.move(-this->speed, 0); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this ->sprite.move(this->speed, 0); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->sprite.move(0, -this->speed); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->sprite.move(0, this->speed);
    }
    updateWallCollision(target); 
}

void Player::render(sf::RenderTarget* target) {
    target->draw(sprite);
}

const sf::Vector2f& Player::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Player::getbounds() const
{
    return sprite.getGlobalBounds(); 
}

