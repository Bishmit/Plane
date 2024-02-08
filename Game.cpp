#include "Game.h"

Game::Game() {
    initVariable();
    initTexture();
    initEnemiesTexture(); 
    initEnemyBulletTexture(); 
    initWindow();
    initEnemies();
    initfont(); 
    makeHealthBar(); 
}

Game::~Game() {
    delete window;

    // deleting bullet textures of player
    for (auto& i : this->textures) {
        delete i.second; // seleting the texture part from the map and deleting it
    }

    // deleting bullet textures of enemies
    for (auto& i : this->EnemyBulletTexture) {
        delete i.second; // seleting the texture part from the map and deleting it
    }

    // deleting enemy textures
    for (auto& i : this->EnemyTextures) {
        delete i.second; // seleting the texture part from the map and deleting it
    }

    // deleting the bullets from vector
    for (auto* i : this->bullets) {
        delete i;
    }

    // deleting the enemy bullets from vector
    for (auto* i : this->Enemybullets) {
        delete i;
    }

    // deleting all enemies shit 
    for (auto& enemy : enemies) {
        delete enemy;
    }
}

void Game::initVariable() {
    endgame = false;
    this->score = 0; 
}

void Game::initWindow() {
    videomode = sf::VideoMode(800, 800);
    window = new sf::RenderWindow(videomode, "Plane", sf::Style::Close | sf::Style::Titlebar);
    backgroundtexture.loadFromFile("Space.png");
    bgsprite.setTexture(backgroundtexture);
    this->window->setFramerateLimit(60);
}

void Game::initTexture()
{
    // give texture for bullets 
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Bullet.png");

}

void Game::initEnemyBulletTexture()
{
    // give texture for Enemy bullets 
    this->EnemyBulletTexture["ENEMYBULLET"] = new sf::Texture();
    this->EnemyBulletTexture["ENEMYBULLET"]->loadFromFile("ReverseBullet.png");

}

void Game::initEnemiesTexture() {
    //gives texture for the enemy 
    this->EnemyTextures[0] = new sf::Texture();
    this->EnemyTextures[0]->loadFromFile("Enemy/Enemy1.png");

    this->EnemyTextures[1] = new sf::Texture();
    this->EnemyTextures[1]->loadFromFile("Enemy/Enemy2.png");

    this->EnemyTextures[2] = new sf::Texture();
    this->EnemyTextures[2]->loadFromFile("Enemy/Enemy3.png");

    this->EnemyTextures[3] = new sf::Texture();
    this->EnemyTextures[3]->loadFromFile("Enemy/Enemy4.png");

}

const bool Game::running() const {
    return window->isOpen();
}

void Game::pollEvents() {
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                window->close();
                break;
            }
        }
    }
}

void Game::update() {
    player.update(this->window);
    spawnBullets();
    updateBullets();
    spawnEnemiesBullet(); 
    updateEnemyBullets(); 
    deletingenemies(); 
    RemoveBullets(); 
    makeEnemyTouchPlayer(); 
    makeEnemyBulletTouchPlayer(); 
}

void Game::render() {
    window->clear();
    window->draw(bgsprite);
    player.render(this->window);
    // rendering the bullets 
    for (auto* bullet : this->bullets) {
        bullet->render(this->window);
    }
    // rendering the enemies 
    for (auto& enemy : enemies) {
        enemy->render(this->window);
    }
    // rendering the enemies bullet
    for (auto* enemybullet :this->Enemybullets) {
        enemybullet->render(this->window);
    }
    window->draw(healthbar); 
    window->draw(text); 
    window->display();
}

void Game::spawnBullets() {
    // Define a cooldown duration (in milliseconds)
    const sf::Time CooldownTime = sf::milliseconds(100); // 100 milliseconds cooldown

    static sf::Clock cooldownClock;
    static bool canShoot = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot) {
        // Create a new bullet and add it to the bullets vector
        this->bullets.push_back(new Bullet(this->textures["BULLET"], player.getPos().x + 16.f, player.getPos().y, 0.f, -2.f, 5.f, 2.f, 2.f));
        //this->bullets.push_back(new Bullet(this->textures["BULLET"], player.getPos().x + 35.f, player.getPos().y, 0.f, -2.f, 5.f, 2.f, 2.f));

        // Start the cooldown timer
        cooldownClock.restart();
        canShoot = false;
    }

    // Check if the cooldown time has elapsed and reset the canShoot flag
    if (!canShoot && cooldownClock.getElapsedTime() >= CooldownTime) {
        canShoot = true;
    }
}

void Game::spawnEnemiesBullet() {
    const sf::Time CooldownTime = sf::milliseconds(1000);

    static sf::Clock cooldownClock;
    static bool canShoot = true;

    // Check if the cooldown time has elapsed and reset the canShoot flag
    if (!canShoot && cooldownClock.getElapsedTime() >= CooldownTime) {
        canShoot = true;
    }

    if (this->score >= 10 && canShoot) {
        for (auto* enemy : enemies) {
            // random enemy will shoot the bullet
            int randomNumber = rand() % 100;
            if (randomNumber<20) {
                EnemyBullet* enemyBullet = new EnemyBullet(
                    this->EnemyBulletTexture["ENEMYBULLET"],
                    enemy->getPos().x + 16.f,
                    enemy->getPos().y,
                    0.f, 2.f, 5.f, 2.f, 2.f
                );
                this->Enemybullets.push_back(enemyBullet);
            }
            // Start the cooldown timer
            cooldownClock.restart();
            canShoot = false;
        }
    }
}


void Game::updateBullets() {
    unsigned index = 0;
    for (auto* bullet : this->bullets) {
        bullet->update(this->window);

        // deleting the bullets if it goes out of the bound
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
            // deleting the bullets
            delete this->bullets[index];
            this->bullets.erase(this->bullets.begin() + index);
        }
        ++index;
    }
}

void Game::updateEnemyBullets() {
    unsigned index = 0;
    for (auto* enemybullet : this->Enemybullets) {
        enemybullet->update(this->window);

        // deleting the bullets if it goes out of the bound
        if (enemybullet->getBounds().top + enemybullet->getBounds().height > 800.f) {
            // deleting the bullets
            delete this->Enemybullets[index];
            this->Enemybullets.erase(this->Enemybullets.begin() + index);
        }
        ++index;
    }
}

void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}

void Game::deletingenemies() {
    //first lets create random enemy shits 
    int randomIndex = rand()% EnemyTextures.size(); 
    //first creating enemies
    this->spawnTimer += 0.5f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        Enemy* newEnemy = new Enemy( this->EnemyTextures[randomIndex]);
        newEnemy->setPosition(sf::Vector2f(rand() % 700, -100));
        enemies.push_back(newEnemy);
        this->spawnTimer = 0.f;
    }
    // deleting the enemies once if they goes outside the bounds
    for (auto* enemy : enemies) {
        enemy->update(); // each enemy got updated
    }
    unsigned index = 0;
    for (auto* e : enemies) {
        if (e->getBounds().top + e->getBounds().height >800.f) {
            delete this->enemies[index];
            this->enemies.erase(this->enemies.begin() + index);
            --index;
            std::cout << this->enemies.size() << "\n";
        }
        ++index;
    }
}


void Game::RemoveBullets() {
    // Iterate over bullets and enemies
    for (int i = 0; i < enemies.size(); i++) {
        for (int j = 0; j < bullets.size(); j++) {
            if (enemies[i]->getBounds().intersects(bullets[j]->getBounds())) {
                // If there's an intersection, remove both the bullet and the enemy
                this->score++; 
                std::cout << score << "\n"; 
                text.setString("Score: " + std::to_string(this->score));
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                delete bullets[j];
                bullets.erase(bullets.begin() + j);
                i--;
                break; 
            }
        }
    }
}

void Game::initfont() {
    if (!font.loadFromFile("Font/PixellettersFull.ttf")) {
        std::cout << "Error: Couldn't load the font file" << std::endl;
    }
    text.setFont(font);
    text.setString("Score: " + std::to_string(this->score));
    text.setPosition(610.f,5.f);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
}

void Game::makeEnemyTouchPlayer() {
    // player enemy collision
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->getBounds().intersects(player.getbounds())) {
            // call the health bar decreasing function here
            DecreaseHp(30.f); 
           // std::cout << "enemy touches player" << "\n"; 
            delete enemies[i]; 
            enemies.erase(enemies.begin() + i);
            break; 
        }
    }
}

void Game::makeEnemyBulletTouchPlayer() {
    // player enemy collision
    for (int i = 0; i < Enemybullets.size(); i++) {
        if (Enemybullets[i]->getBounds().intersects(player.getbounds())) {
            // call the health bar decreasing function here
            DecreaseHp(10.f);
           // std::cout << "enemy touches player" << "\n"; 
            delete Enemybullets[i];
            Enemybullets.erase(Enemybullets.begin() + i);
            break;
        }
    }
}

void Game::makeHealthBar() {
    // making health bar type thing in window which decreases the health as the player touches enemy bullets or enemy 
    healthbar.setPosition(10.f, 10.f); 
    healthbar.setFillColor(sf::Color::Red); 
    healthbar.setSize(sf::Vector2f(150.f, 15.f)); 
}

void Game::DecreaseHp(float number) {
    // decreasing the hp 
        newhp.x = healthbar.getSize().x - number;
        newhp.y = healthbar.getSize().y;
        if (newhp.x <= 0.0f) {
            newhp.x = 0.0f;
            std::cout << "Gameover" << "\n"; 
        }
        healthbar.setSize(sf::Vector2f(newhp.x, newhp.y));
}







