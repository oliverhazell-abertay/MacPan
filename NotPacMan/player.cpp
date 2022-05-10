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

	// Update shape
	playerShape.setPosition(position);
}
