#include "player.h"

void Player::Update()
{
	// Eat dots
	if (currentNode)
		currentNode->type = TileType::blank;

	// Update next Node
	// If moving laterally
	if (direction.x != 0.0f)
		nextNode = (direction.x < 0.0f) ? leftAdj : rightAdj;
	// If moving vertically
	if (direction.y != 0.0f)
		nextNode = (direction.y < 0.0f) ? upAdj : downAdj;
	// If not moving
	if (direction.x == 0.0f && direction.y == 0.0f)
		nextNode = NULL;

	// Collision detection
	// Moving left
	if (nextNode && nextNode == leftAdj && nextNode->type == TileType::obstacle)
	{
		if (position.x <= nextNode->GetWorldPos().x + playerShape.getSize().x)
		{
			direction.x = 0.0f;
			position.x = currentNode->GetWorldPos().x;
		}
	}
	// Moving right
	if (nextNode && nextNode == rightAdj && nextNode->type == TileType::obstacle)
	{
		if (position.x >= nextNode->GetWorldPos().x - playerShape.getSize().x)
		{
			direction.x = 0.0f;
			position.x = currentNode->GetWorldPos().x;
		}
	}
	// Moving up
	if (nextNode && nextNode == upAdj && nextNode->type == TileType::obstacle)
	{
		if (position.y <= nextNode->GetWorldPos().y + playerShape.getSize().y)
		{
			direction.y = 0.0f;
			position.y = currentNode->GetWorldPos().y;
		}
	}
	// Moving down
	if (nextNode && nextNode == downAdj && nextNode->type == TileType::obstacle)
	{
		if (position.y >= nextNode->GetWorldPos().y - playerShape.getSize().y)
		{
			direction.y = 0.0f;
			position.y = currentNode->GetWorldPos().y;
		}
	}

	// Update shape
	playerShape.setPosition(position);
}
