#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Atirador bigodudo",sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/Bullet.png");


}

void Game::initPlayer()
{
	 this->spawnTimer = this->spawnTimerMax;
	 this-> spawnTimerMax = 20.f;
	this->player = new Player();

}

void Game::initEnemies()
{

}

//Con/Des
Game::Game()
{

	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures) {
		delete i.second;
	}
	//Delete Bullets
	for (auto* i : this->bullets) {
		delete i;
	}
	//Delete Enemies
	for (auto* i : this->enemies) {
		delete i;
	}
}

//Functions

void Game::run()
{
	while (window->isOpen()) 
	{

	this->update();

	this->render();

	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed) {
			this->window->close();
		}
		if (e.Event::type && e.Event::key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		this->player->move(-1.f, 0.f);
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		this->player->move(1.f, 0.f);

	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		this->player->move(0.f, -1.f);

	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		this->player->move(0.f, 1.f);

	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) {
		this->bullets.push_back(new Bullet(this->textures["BULLET"],this->player->getPos().x + this->player->getBounds().width/2.f,
			this->player->getPos().y
			, 0.f, -1.f, 10.f));
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;

	for (auto* bullet : this->bullets) {
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin()+ counter);
			--counter;

			//Balas são deletadas? OK
			//std::cout << this->bullets.size() << "\n";
		}
		counter++;
	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer > this->spawnTimerMax) {

		this->enemies.push_back(new Enemy(rand()%200, rand()% 200));
		this->spawnTimer = 0.f;
	}
	for (auto* enemy : this->enemies) {
		enemy->update();
	}
	
}

void Game::update()
{
	this->updatePollEvents();

	this->updateInput();

	this->player->update();
	
	this->updateBullets();

	this->updateEnemies();
}

void Game::render()
{
	//Clear
	this->window->clear();
	//Draw stuff

	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}

	//Display stuff
	this->window->display();
}
