#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "globals.h"
#include "Bullet.h"
#include "Enemy.h"
class Game {
private:
    sf::Texture backgroundtexture;
    sf::Sprite bgsprite;
    float endgame;
    sf::RenderWindow* window;
    sf::VideoMode videomode;
    sf::Event event;
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies; 
    sf::Font font; 
    sf::Text text; 
    int score = 0; 
    float spawnTimer;
    float spawnTimerMax;
    Player player;
    void initVariable();
    void initWindow();
    void initTexture();
    void pollEvents();
    void initEnemies();
    void initfont();

public:
    Game();
    ~Game();

    const bool running() const;
    void update();
    void render();
    void spawnBullets();
    void updateBullets();

  

    void deletingenemies();

    void RemoveBullets();

   


};