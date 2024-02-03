#include "Game.h"

Game::Game() {
    initVariable();
    initTexture(); 
    initWindow();
}

Game::~Game() {
    delete window;

    // deleting textures
    for (auto &i : this->textures) {
        delete i.second; // seleting the texture part from the map and deleting it
    }

    // deleting the bullets 
    for (auto* i : this->bullets) {
        delete i; 
    }

    // 
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
}
void Game::render() {
    window->clear();
    window->draw(bgsprite);
    player.render(this->window);
    // rendering the bullets 
    for (auto* bullet : this->bullets) {
        bullet->render(this->window); 
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
        this->bullets.push_back(new Bullet(this->textures["BULLET"], player.getPos().x, player.getPos().y, 0.f, -2.f, 5.f, 2.f,2.f));

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
            std::cout << this->bullets.size() << "\n"; 
        }
        ++index; 
    }
}


