#include<SFML/Graphics.hpp>
#include<iostream>

#pragma once
class EnemyBullet
{
	sf::Sprite shape;
	sf::Vector2f direction;
	float movementspeed;
public:
	EnemyBullet();
	EnemyBullet(sf::Texture* Enemybulltex, float pos_x, float pos_y, float dir_x, float dir_y, float movementspeed, float size_x, float size_y);
	virtual ~EnemyBullet();
	const sf::FloatRect getBounds() const;

	void update(sf::RenderTarget* target);

	void render(sf::RenderTarget* target);

};

