#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "globals.h"
#include "Bullet.h"
#include "Enemy.h"
#include"EnemyBullet.h"
#include "Powerup.h"
#include"SpecialEnemy.h"
#include"BossEnemy.h"
#include"LethalEnemy.h"
#include <cstdlib> 
#include <ctime>   
#include<memory>
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
    std::map<int, sf::Texture*> PowerupTextures;
    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies; 
    std::vector<EnemyBullet*> Enemybullets;
    std::vector<Powerup*> Powerupvector;
    std::vector<std::unique_ptr<SpecialEnemy>>specialenemies; 
    sf::Font font; 
    sf::Text text; 

    int score; 
    float spawnTimer;
    float spawnTimerMax;

    // for powerup entities
    float spawnTimerHP; 
    float spawnTimerMaxHP; 

    Player player;
    void initVariable();
    void initWindow();
    void initTexture();
    void initEnemyBulletTexture();
    void initEnemiesTexture();
    void inithealthbarentities(); 
    void initEnemies();
    void initPoweupEntities();
    void initfont();
    //void initSound(); 

    void makeEnemyTouchPlayer();

    void makeEnemyBulletTouchPlayer();

    void makeHealthBar();

    void DecreaseHp(float);
    void increaseHp(float);
    void initspecialenemy(); 

public:
    Game();
    ~Game();

    const bool running() const;
    void pollEvents();
    void Update();
    void render();
    void spawnBullets();
    void spawnEnemiesBullet();
    void updateBullets();

    void updateEnemyBullets();

  

    void deletingenemies();

    void RemoveBullets();
    void SpawnAndDeletePowerup(); 
    void makePowerupTouchPlayer();
    void updatespecialenemy();

};