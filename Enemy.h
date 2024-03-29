#pragma once
#include <SFML/Graphics.hpp>
#include"globals.h"
class Enemy {
private:
    sf::Sprite enemy;

public:
    Enemy(sf::Texture *enemyTexture);
    ~Enemy();
    void update();
    void render(sf::RenderWindow* window); 
    const sf::FloatRect getBounds() const;
    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPos() const;
};


