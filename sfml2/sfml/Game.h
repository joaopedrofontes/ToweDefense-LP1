#pragma once

#include <iostream>
#include <ctime>



#include "Player.h"

/*
	Class that acts as the game engine / wrapper class.
*/

class Game
{
private:
	//Private variables
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	//Initializers
	void initVariables();
	void initWindow();
public:
	//Constructors and Destructors
	Game();
	~Game();
	//Accessors

	//Modifiers

	//Functions
	const bool running() const;
	void pollEvents();

	void update();
	void render();
};

