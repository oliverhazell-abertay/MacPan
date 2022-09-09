#include "player.h"

Player::Player(sf::Vector2f startPos, sf::Vector2f size, float startSpeed)
{
	// Init position
	position = startPos;
	shape.setPosition(position);
	// Init shape
	shape.setSize(size);
	shape.setFillColor(sf::Color::Yellow);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(0.0f);
	// Init speed
	SetSpeed(startSpeed);
}

void Player::Update(float dt)
{
	// Update gameObject
	GameObject::Update(dt);
	// Eat pellets
	EatPellets();
	// Powered timer
	if (powered)
	{
		// Increment timer
		powerTimer += dt;
		// End timer
		if (powerTimer >= powerDuration)
		{
			powered = false;
			powerTimer = 0.0f;
		}
	}
}

void Player::EatPellets()
{
	// Eat dots
	if (currentNode->type == TileType::pellet)
		currentNode->type = TileType::blank;
	// Eat power pellets
	if (currentNode->type == TileType::power)
	{
		powered = true;
		currentNode->type = TileType::blank;
	}
}