#include "Enemy.h"

Enemy::Enemy() {
    if (!texture.loadFromFile("enemy.png")) {
        // Handle error
    }
    enemy.setTexture(texture);
    enemy.setScale(sf::Vector2f(0.5f, 0.5f));
}

Enemy::~Enemy() {

}

void Enemy::update() {
    // Update enemy behavior
    sf::Vector2f position = enemy.getPosition();
    position.y += 1.0f; // Adjust the speed of movement
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
