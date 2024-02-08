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

    Player(float x = 400.f, float y = 600.f);
    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
    const sf::Vector2f& getPos() const;
    const sf::FloatRect getbounds() const; 
}; 