#include "node.h"

Node::Node()
{
}

void Node::Init(sf::Vector2f initWorldPos, sf::Vector2f initSize, sf::Vector2i gridPosition, TileType initType)
{
	worldPos = initWorldPos;
	size = initSize;
	gridPos = gridPosition;
	type = initType;

	// Init shapes
	// Tile
	tile.setSize(size);
	tile.setPosition(worldPos);

	// Pellet
	pellet.setRadius(size.x * 0.1f);
	pellet.setFillColor(sf::Color::White);
	// Position in the middle of tile
	sf::Vector2f tempPos = worldPos;
	tempPos.x = tempPos.x + (size.x * 0.4f);
	tempPos.y = tempPos.y + (size.y * 0.4f);
	pellet.setPosition(tempPos);

	// Power pellet
	powerPellet.setRadius(size.x * 0.25f);
	powerPellet.setFillColor(sf::Color::Yellow);
	// Position in the middle of tile
	tempPos = worldPos;
	tempPos.x = tempPos.x + (size.x * 0.25f);
	tempPos.y = tempPos.y + (size.y * 0.25f);
	powerPellet.setPosition(tempPos);
}

void Node::Render(sf::RenderWindow* window)
{
	// If obstacle, set tile to black, if not then reset to white
	if (type == TileType::obstacle)
		tile.setFillColor(sf::Color::Blue);
	else
		tile.setFillColor(sf::Color::Black);
	// Render tile
	window->draw(tile);
	// Render pellet or power pellet depending on tile type
	if (type == TileType::pellet)
		window->draw(pellet);
	if (type == TileType::power)
		window->draw(powerPellet);
}

void Node::CalculateFGH(Node* startNode, Node* endNode)
{
	// If not start or end node work out distances
	if (startNode->gridPos != gridPos || endNode->gridPos != gridPos)
	{
		gCost = CalculateG(startNode);
		hCost = CalculateH(endNode);
		fCost = CalculateF();
	}
}

int Node::CalculateG(Node* startNode)
{
	int startNodeX, startNodeY;
	startNodeX = startNode->gridPos.x;
	startNodeY = startNode->gridPos.y;
	// x distance
	int xDistance = abs(gridPos.x - startNodeX);
	// y distance
	int yDistance = abs(gridPos.y - startNodeY);

	return xDistance + yDistance;
}

int Node::CalculateH(Node* endNode)
{
	int endNodeX, endNodeY;
	endNodeX = endNode->gridPos.x;
	endNodeY = endNode->gridPos.y;
	// x distance
	int xDistance = abs(gridPos.x - endNodeX);
	// y distance
	int yDistance = abs(gridPos.y - endNodeY);

	return xDistance + yDistance;
}

int Node::CalculateF()
{
	return gCost + hCost;
}