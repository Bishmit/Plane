#pragma once
#include<SFML/Graphics.hpp>
class Powerup
{
private: 
	sf::Sprite hp;
public: 
	Powerup(sf::Texture* hptex); 

	void update(); 
	void render(sf::RenderWindow* target);
	const sf::FloatRect getBounds() const;

	void setPosition(const sf::Vector2f& position);

	const sf::Vector2f& getPos() const;

};

