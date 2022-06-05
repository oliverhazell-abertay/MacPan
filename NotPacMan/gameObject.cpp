#include "gameObject.h"
#include "player.h"

void GameObject::Update()
{
	// Update next node
	GetNextNode();

	// Collision detection - Check next node in direction game object is headed.
	//						 If next node is obstacle, stop moving
	// Moving left
	if (nextNode && nextNode == leftAdj && nextNode->type == TileType::obstacle)
	{
		if (position.x <= nextNode->GetWorldPos().x + shape.getSize().x)
		{
			direction.x = 0.0f;
			position.x = currentNode->GetWorldPos().x;
		}
	}
	// Moving right
	if (nextNode && nextNode == rightAdj && nextNode->type == TileType::obstacle)
	{
		if (position.x >= nextNode->GetWorldPos().x - shape.getSize().x)
		{
			direction.x = 0.0f;
			position.x = currentNode->GetWorldPos().x;
		}
	}
	// Moving up
	if (nextNode && nextNode == upAdj && nextNode->type == TileType::obstacle)
	{
		if (position.y <= nextNode->GetWorldPos().y + shape.getSize().y)
		{
			direction.y = 0.0f;
			position.y = currentNode->GetWorldPos().y;
		}
	}
	// Moving down
	if (nextNode && nextNode == downAdj && nextNode->type == TileType::obstacle)
	{
		if (position.y >= nextNode->GetWorldPos().y - shape.getSize().y)
		{
			direction.y = 0.0f;
			position.y = currentNode->GetWorldPos().y;
		}
	}

	// Update shape position for render
	shape.setPosition(position);
}

void GameObject::GetNextNode()
{
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
}