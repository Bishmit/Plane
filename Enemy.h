#pragma once
#include <SFML/Graphics.hpp>
#include"globals.h"
class Enemy {
private:
    sf::Sprite enemy;
    void initVariables();
    void initShape();

public:
    Enemy(sf::Texture *enemyTexture);
    ~Enemy();
    void update();
    void render(sf::RenderWindow* window); 
    const sf::FloatRect getBounds() const;
    void setPosition(const sf::Vector2f& position);
};


