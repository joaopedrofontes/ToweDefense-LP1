#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

    //Game logic
    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Honk_Regular.ttf")) {
        std::cout << "ERROR::GAME::INITFONTS::FAILED TO LOAD FONT!" << std::endl;
    }
}

void Game::initText() 
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");

}





void Game::initEnemies()
{
    this->enemy.setPosition(10.f,10.f);
    this->enemy.setSize(sf::Vector2f(100.f,100.f));
    this->enemy.setFillColor(sf::Color::Blue);
    //this->enemy.setOutlineColor(sf::Color::Green);
   // this->enemy.setOutlineThickness(2.f);


}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return false;
}




//Functions
void Game::spawnEnemy()
{
    /* @return void
    
    Spawns enemies and sets their colors and random positions and types.
    -  sets a random type
     - sets a random position
     - sets a random color.
     - Adds enemy to the vector
    */

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    //Randomize enemy type
    int type = rand() % 5;

    switch (type) {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Green);
        break;
    default:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    }

   

    //Spawn the enemy
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
    //Event pooling
    while (this->window->pollEvent(this->ev)) {

        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;

        }
    }
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points: " << this->points << "\n"
        << "Health: " << this->health << "\n";

    this->uiText.setString(ss.str());
}

void Game::updateMousePositions()
{
    /* return void
    * 
    * -updates the mouse positions:
    *   -Relative to the window (Vector2i)
    */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
    /* @return void
    * 
    * Updates the enemy spawn timer and spawns enemies.
      Moves the enemies 
    */
    //Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {

        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) 
    {
        //Spawn the enemy and reset the timer
        this->spawnEnemy();
        this->enemySpawnTimer = 0.f;
    }
    else 
    {
        this->enemySpawnTimer += 1.f;
    }
    }

    //Move the enemies and updating enemies
    for (int i = 0;i < this->enemies.size();i++) 
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 5.f);

        //If the enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health-=1;
            std::cout << "health: " << this->health << "\n";
        }
    }

    //Check if clicked upon
    //Whenever we click within the bounds of an enemy, we kill it
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {

                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    //Gain points
                    if(this->enemies[i].getFillColor()==sf::Color::Magenta)
                    this->points += 10;
                    else if(this->enemies[i].getFillColor()==sf::Color::Blue)
                        this->points += 7;
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->points += 5;
                    else if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 3;
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 1;

                    std::cout << "Points: " << this->points << "\n";

                    //Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                }

            }
        }
        
    }
    else {
        this->mouseHeld = false;
    }

    

}


void Game::update()
{
    this->pollEvents();

    if (!this->endGame) {
    this->updateMousePositions();

    this->updateText();

    this->updateEnemies();
}
    //Condi��o de fim de jogo
    if (this->health <= 0) {
        this->endGame = true;
    }
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    //Rendering all the enemies
    for (auto& e : this->enemies) {
        target.draw(e);
    }
}

void Game::render()
{
    /*
    @return void

    * -Clear old frame
    * -render objects
    * -display frame in window
    * 
        Renders the game objects.
    */

    this->window->clear();

    //Draw game objects
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}
