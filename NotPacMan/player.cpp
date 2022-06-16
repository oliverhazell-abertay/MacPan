#include "player.h"

void Player::Update(float dt)
{
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
	// Update gameObject
	GameObject::Update();
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