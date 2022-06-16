#include "enemy.h"

void Enemy::Init(Node grid[GRID_WIDTH][GRID_HEIGHT], Player* targetPlayer, Node* home)
{
	// Init pathfinder
	pathfinder.Init(grid);
	// Target player
	player = targetPlayer;
	// Init home node
	homeNode = home;
	// Flash colours
	flashColourLight = sf::Color(0, 65, 163, 255);
	flashColourDark = sf::Color(0, 50, 128, 255);
}

void Enemy::Update(float dt)
{
	// Colour management
	if (player->powered)
		Flash(dt);
	else
		currentColour = mainColour;
	shape.setFillColor(currentColour);

	// If target node has been reached
	if (targetReached)
	{
		// If player isn't empowered, pursue player
		if (!player->powered)
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
		// If player is empowered, head home
		if (player->powered)
		{
			pathfinder.SetStart(currentNode);
			pathfinder.SetEnd(homeNode);
			pathfinder.FindPath();
			targetReached = false;
		}
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
		targetReached = true;
	}
}

bool Enemy::FuzzyEquals(float a, float b, float tolerance)
{
	return std::abs(a - b) <= tolerance;
}

void Enemy::Flash(float dt)
{
	// Increment timer
	flashTimer += dt;

	// If timer has expired, flip colour
	if (flashTimer >= flashFreq)
	{
		// If light colour, flip to dark and vice verca
		currentColour = (currentColour == flashColourLight) ? flashColourDark : flashColourLight;
		// Reset timer
		flashTimer = 0.0f;
	}
}