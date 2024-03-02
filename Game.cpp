#include "Game.h"

Game::Game() {
    initVariable();
    initTexture();
    initEnemiesTexture(); 
    initEnemyBulletTexture(); 
    initWindow();
    initEnemies();
    initPoweupEntities(); 
    inithealthbarentities();
    initfont(); 
    makeHealthBar(); 
    initspecialenemy();
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

    // deleting powerup textures
    for (auto& i : this->PowerupTextures) {
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

    // deleting all powerup shit 
    for (auto& hp : Powerupvector) {
        delete hp;
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

    this->EnemyTextures[4] = new sf::Texture();
    this->EnemyTextures[4]->loadFromFile("Enemy/Enemy5.png");

    this->EnemyTextures[5] = new sf::Texture();
    this->EnemyTextures[5]->loadFromFile("Enemy/Enemy6.png");

}

void Game::inithealthbarentities() {
    this->PowerupTextures[0] = new sf::Texture(); 
    this->PowerupTextures[0]->loadFromFile("PowerUpEntity/hpSupply.png"); 

    this->PowerupTextures[1] = new sf::Texture();
    this->PowerupTextures[1]->loadFromFile("PowerUpEntity/hpSupply2.png");
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

void Game::Update() {
    player.update(this->window);
    spawnBullets();
    updateBullets();
    spawnEnemiesBullet(); 
    updateEnemyBullets(); 
    deletingenemies(); 
    RemoveBullets(); 
    deleteCollisoneffectOnceDone(); 
    SpawnAndDeletePowerup(); 
    makeEnemyTouchPlayer(); 
    makeEnemyBulletTouchPlayer(); 
    makePowerupTouchPlayer(); 

    for (auto& i : particle) {
        i->update(); 
    }
    updatespecialenemy(); 
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
    // redering the powerup in the screen
    for (auto* hpbarshit : this->Powerupvector) {
        hpbarshit->render(this->window); 
    }

    for (auto& particle_ : particle) {
        particle_->render(this->window); 

    for (auto& enemy : specialenemies) {
        enemy->draw(window); 

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

void Game::initPoweupEntities()
{
    this->spawnTimerMaxHP = 50.f;
    this->spawnTimerHP = this->spawnTimerMaxHP;
}

void Game::initspecialenemy()
{
    specialenemies.push_back(std::make_unique<BossEnemy>()); // making the new pointer of the boss enemy and pushing that shit to vector

    specialenemies.push_back(std::make_unique<LethalEnemy>()); //same we do for lethal enemy both of them goes to the same vector of specialenemy pointer
         /*
     vector fucking don't know what is happening and can't diffrentiate anything, the special enemy pointer is knowing the stuffs on the basis of pointer this shit is called 
     runtime polymorphism
    */ 
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
           // std::cout << this->enemies.size() << "\n";
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
                makePostCollisonEffect(i,j);
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

void Game::SpawnAndDeletePowerup() {
    int randomIndex = rand() % PowerupTextures.size();
    this->spawnTimerHP += 0.5f/40;
    if (this->spawnTimerHP >= this->spawnTimerMaxHP)
    {
        Powerup* newhp = new Powerup(this->PowerupTextures[randomIndex]);
        newhp->setPosition(sf::Vector2f(rand() % 700, -100));
        Powerupvector.push_back(newhp);
        this->spawnTimerHP = 0.f;
    }

    for (auto* healthentity : Powerupvector) {
        healthentity->update(); 
    }
    unsigned index = 0;
    for (auto* hp : Powerupvector) {
        if (hp->getBounds().top + hp->getBounds().height > 800.f) {
            delete this->Powerupvector[index];
            this->Powerupvector.erase(this->Powerupvector.begin() + index);
            --index;
           // std::cout << "chalexa" << "\n";
        }
        ++index;
    }
}

void Game::makePowerupTouchPlayer() {
    // player enemy collision
    for (int i = 0; i < Powerupvector.size(); i++) {
        if (Powerupvector[i]->getBounds().intersects(player.getbounds())) {
            // call the health bar decreasing function here
            increaseHp(20.f);
            // std::cout << "enemy touches player" << "\n"; 
            delete Powerupvector[i];
            Powerupvector.erase(Powerupvector.begin() + i);
            break;
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
            DecreaseHp(20.f);
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

void Game::increaseHp(float number) {
    // decreasing the hp 
    newhp.x = healthbar.getSize().x + number;
    newhp.y = healthbar.getSize().y;
    if (newhp.x >= 150.0f) {
        newhp.x = 150.0f;
    }
    healthbar.setSize(sf::Vector2f(newhp.x, newhp.y));
}

void Game::makePostCollisonEffect(int i, int j) {
        std::unique_ptr<ParticleSystem> newParticle = std::make_unique<ParticleSystem>(
            0.f,
            0.f,
            0.f
        );
        newParticle->setPosition(sf::Vector2f(enemies[i]->getPos().x, enemies[i]->getPos().y)); 
        particle.push_back(std::move(newParticle));
       // std::cout << enemies[i]->getPos().x << " " << enemies[i]->getPos().y << "\n";

        // Reset the clock to restart the timer
}


void Game::deleteCollisoneffectOnceDone() {
    auto it = std::remove_if(particle.begin(), particle.end(), [&](const std::unique_ptr<ParticleSystem>& p) {
        return p->getbounds().left < -50.f;
        }); 
    particle.erase(it, particle.end()); 
}


void Game::updatespecialenemy() {
    for (auto& enemyptr : specialenemies) {
        enemyptr->update();
    }
  }







