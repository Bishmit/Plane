#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "globals.h"
#include "Bullet.h"
#include "Enemy.h"
#include"EnemyBullet.h"
#include <cstdlib> 
#include <ctime>   
class Game {
private:
    sf::Vector2f newhp; 
    sf::RectangleShape healthbar; 
    sf::Texture backgroundtexture;
    sf::Sprite bgsprite;
    float endgame;
    sf::RenderWindow* window;
    sf::VideoMode videomode;
    sf::Event event;
    std::map<std::string, sf::Texture*> textures;  //player bullet texture 
    std::map<std::string, sf::Texture*> EnemyBulletTexture;  //enemy bullet texture 
    std::map<int, sf::Texture*> EnemyTextures; 
    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies; 
    std::vector<EnemyBullet*> Enemybullets;
    sf::Font font; 
    sf::Text text; 
    int score; 
    float spawnTimer;
    float spawnTimerMax;
    Player player;
    void initVariable();
    void initWindow();
    void initTexture();
    void initEnemyBulletTexture();
    void initEnemiesTexture();
    void initEnemies();
    void initfont();

    void makeEnemyTouchPlayer();

    void makeEnemyBulletTouchPlayer();

    void makeHealthBar();

    void DecreaseHp(float);

public:
    Game();
    ~Game();

    const bool running() const;
    void pollEvents();
    void update();
    void render();
    void spawnBullets();
    void spawnEnemiesBullet();
    void updateBullets();

    void updateEnemyBullets();

  

    void deletingenemies();

    void RemoveBullets();

};