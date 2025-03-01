#pragma once
#include<SFML/Graphics.hpp>
class ParticleSystem
{
private: 
	sf::RectangleShape shape; 
	sf::Vector2f velocity; 
	sf::Vector2f pos; 
	sf::Texture texture; 
	sf::Sprite sprite; 
	float movement; 

public:
	ParticleSystem(float vel_x, float vel_y, float movement); 

	//public function
	void update(); 
	void render(sf::RenderTarget* target); 
	sf::FloatRect getbounds();
	void setPosition(const sf::Vector2f& position);
};

