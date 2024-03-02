#pragma once
#include"SpecialEnemy.h"
#include"iostream"
class BossEnemy:public SpecialEnemy
{
private: 
	sf::Texture tex; 
	sf::Sprite sprite; 

public: 
	BossEnemy();

	void update() override; 
	void draw(sf::RenderWindow* window); 

};

