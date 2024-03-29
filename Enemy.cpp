#include "Enemy.h"

Enemy::Enemy(sf::Texture *enemyTexture) {
    
    enemy.setTexture(*enemyTexture);
    enemy.setScale(sf::Vector2f(1.f, 1.f));
}

Enemy::~Enemy() {

}

void Enemy::update() {
    // Update enemy behavior
    sf::Vector2f position = enemy.getPosition();
    position.y += 1.5f; // Adjust the speed of movement
    enemy.setPosition(position);
}

void Enemy::render(sf::RenderWindow *window) {
    // Render enemy
    window->draw(enemy); 
}

const sf::FloatRect Enemy::getBounds() const {
    return enemy.getGlobalBounds();
}

void Enemy::setPosition(const sf::Vector2f& position) {
    enemy.setPosition(position); // Set the position of the sprite
}

const sf::Vector2f& Enemy::getPos() const
{
    return enemy.getPosition(); 
}
