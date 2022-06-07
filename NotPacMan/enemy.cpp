#include "enemy.h"

void Enemy::Init(Node grid[GRID_WIDTH][GRID_HEIGHT], Player* targetPlayer)
{
	// Init pathfinder
	pathfinder.Init(grid);
	// Target player
	player = targetPlayer;
}

void Enemy::Update()
{
	// If target node has been reached
	if (targetReached)
	{
		// If player has moved, recalculate path to player
		if (player->currentNode != lastPlayerNode)
		{
			pathfinder.SetStart(currentNode);
			pathfinder.SetEnd(player->currentNode);
			pathfinder.FindPath();
			targetReached = false;
		}
		// If player hasn't moved, move to next node in path
		if (player->currentNode == lastPlayerNode && !pathfinder.path.empty())
		{
			pathfinder.path.pop_back();
			targetReached = false;
		}
		// Store player position for next check
		lastPlayerNode = player->currentNode;
	}
	// Set target to next node in path
	if(!pathfinder.path.empty())
		target = *pathfinder.path.back();
	// Keep moving towards target
	if (!targetReached)
		MoveTowardsTarget();
	// Update gameObject
	GameObject::Update();
}

void Enemy::MoveTowardsTarget()
{
	// Head towards target
	// If target node is left or right
	if (target.gridPos.x != currentNode->gridPos.x)
	{
		direction.x = (target.gridPos.x < currentNode->gridPos.x) ? -1.0f : 1.0f;
		direction.y = 0.0f;
	}
	// If target node is up or down
	if (target.gridPos.y != currentNode->gridPos.y)
	{
		direction.x = 0.0f;
		direction.y = (target.gridPos.y < currentNode->gridPos.y) ? -1.0f : 1.0f;
	}
	// Check if target has been reached
	if (FuzzyEquals(position.x, target.GetWorldPos().x, 2.0f)
		&& FuzzyEquals(position.y, target.GetWorldPos().y, 2.0f))
	{
		//direction = sf::Vector2f(0.0f, 0.0f);
		targetReached = true;
	}
}

bool Enemy::FuzzyEquals(float a, float b, float tolerance)
{
	return std::abs(a - b) <= tolerance;
}