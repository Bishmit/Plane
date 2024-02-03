#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Texture tex; 
    sf::Sprite sprite; 
    float speed;

    void initVariable();
    void initsprite();
    void updateWallCollision(const sf::RenderTarget* target);

public:

    Player(float x = 0.f, float y = 0.f);
    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
    const sf::Vector2f& getPos() const;
}; 