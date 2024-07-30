#include "Player.h"

void Player::initVariables()
{

this->movementSpeed = 10.f;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));

}

//Moves the player and initializes it
Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

void Player::updateInput()
{
	//Keyboard input
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed,0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->shape.move(0.f, this->movementSpeed);
		}
}

void Player::update(sf::RenderTarget* target)
{
	//Window bounds collision
	

	this->updateInput();


}

//Rendering the player on the screen
void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
