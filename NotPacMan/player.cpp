#include "player.h"

void Player::Update()
{
	// Eat pellets
	EatPellets();
	// Update gameObject
	GameObject::Update();
	
}

void Player::EatPellets()
{
	// Eat dots
	if (currentNode->type == TileType::pellet)
		currentNode->type = TileType::blank;
}