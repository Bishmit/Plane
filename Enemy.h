#pragma once
#include <SFML/Graphics.hpp>
#include"globals.h"
class Enemy {
private:
    sf::Texture texture;
    sf::Sprite enemy;
    void initVariables();
    void initShape();

public:
    Enemy();
    ~Enemy();
    void update();
    void render(sf::RenderWindow* window); 
    const sf::FloatRect getBounds() const;
    void setPosition(const sf::Vector2f& position);
};


