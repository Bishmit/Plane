#include "Game.h"

Game::Game() {
    initVariable();
    initTexture();
    initWindow();
    initEnemies();
}

Game::~Game() {
    delete window;

    // deleting textures
    for (auto& i : this->textures) {
        delete i.second; // seleting the texture part from the map and deleting it
    }

    // deleting the bullets 
    for (auto* i : this->bullets) {
        delete i;
    }

    // deleting all enemies shit 
    for (auto& enemy : enemies) {
        delete enemy;
    }
}

void Game::initVariable() {
    endgame = false;
}

void Game::initWindow() {
    videomode = sf::VideoMode(800, 800);
    window = new sf::RenderWindow(videomode, "Plane", sf::Style::Close | sf::Style::Titlebar);
    backgroundtexture.loadFromFile("Desert.png");
    bgsprite.setTexture(backgroundtexture);
    this->window->setFramerateLimit(60);
}

void Game::initTexture()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Bullet.png");
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
    pollEvents();
    player.update(this->window);
    spawnBullets();
    updateBullets();
    deletingenemies(); 
    RemoveBullets(); 
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
    window->display();
}

void Game::spawnBullets() {
    // Define a cooldown duration (in milliseconds)
    const sf::Time CooldownTime = sf::milliseconds(100); // 100 milliseconds cooldown

    static sf::Clock cooldownClock;
    static bool canShoot = true;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canShoot) {
        // Create a new bullet and add it to the bullets vector
        this->bullets.push_back(new Bullet(this->textures["BULLET"], player.getPos().x, player.getPos().y, 0.f, -2.f, 5.f, 2.f, 2.f));
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


void Game::updateBullets() {
    unsigned index = 0;
    for (auto* bullet : this->bullets) {
        bullet->update(this->window);

        // deleting the bullets if it goes out of the bound
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
            // deleting the bullets
            delete this->bullets[index];
            this->bullets.erase(this->bullets.begin() + index);
            --index;
           // std::cout << this->bullets.size() << "\n";
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
    //first creating enemies
    this->spawnTimer += 0.5f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        Enemy* newEnemy = new Enemy();
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









