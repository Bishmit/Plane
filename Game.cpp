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
    //RemoveEnemies(); 
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

void Game::initEnemies() {
    for (int i = 0; i < 100; ++i) {
        Enemy* newEnemy = new Enemy(); 
        newEnemy->setPosition(sf::Vector2f(rand() % 800, -100 - i * 50)); // Random position
        enemies.push_back(newEnemy);
    }

}

void Game::deletingenemies() {
    // deleting the enemies once if they goes outside the bounds
    for (auto* enemy : enemies) {
        enemy->update(); // each enemy got updated
    }
    unsigned index = 0;
    for (auto* e : enemies) {
        if (e->getBounds().top + e->getBounds().height >600.f) {
            delete this->enemies[index];
            this->enemies.erase(this->enemies.begin() + index);
            --index;
            std::cout << this->enemies.size() << "\n";
        }
        ++index;
    }
}

void Game::RemoveEnemies() {
    std::vector<int> enemiesToRemove; 

    // Iterate over bullets
    for (int i = 0; i < bullets.size(); i++) {
        auto& b = bullets[i];

        // Iterate over enemies
        for (int j = 0; j < enemies.size(); j++) {
            auto& e = enemies[j];

            if (b->getBounds().intersects(e->getBounds())) {
                // Store index of enemy to remove
                enemiesToRemove.push_back(j);
                std::cout << "Collision Occurs" << "\n";
                // post collision logic here 
            }
        }
    }

    // Remove enemies outside the loop
    for (int index : enemiesToRemove) {
        delete enemies[index];
        enemies.erase(enemies.begin() + index);
    }
}


void Game::RemoveBullets() {
    // Iterate over bullets in reverse order
    for (auto* bullet : bullets) {
        bullet->update(window); // each enemy got updated
    }

    for (auto* enemy : enemies) {
        enemy->update(); // each enemy got updated
    }
    for (int i = enemies.size() - 1; i >= 0; i--) {
        for (int j = bullets.size() - 1; j >= 0; j--) {
            if (enemies.at(i)->getBounds().intersects(bullets.at(j)->getBounds())) {
                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);
                delete this->bullets[j];
                this->bullets.erase(this->bullets.begin() + j);
            }
        }
    }
}








