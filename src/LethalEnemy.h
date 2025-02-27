#pragma once
#include"SpecialEnemy.h"
#include"iostream"
class LethalEnemy :public SpecialEnemy
{
private:
	sf::Texture tex;
	sf::Sprite sprite;

public:
	LethalEnemy();

	void update() override;
	void draw(sf::RenderWindow* window);

};
