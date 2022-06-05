#pragma once
#include <SFML/Graphics.hpp>

enum class TileType {blank, pellet, power, obstacle};

class Node
{
public:
	Node();
	void Init(sf::Vector2f initWorldPos, sf::Vector2f initSize, sf::Vector2i gridPosition, TileType initType);
	void Render(sf::RenderWindow* window);

	// Position in array
	sf::Vector2i gridPos;
	// Getters and Setters
	int GetFCost() { return fCost; }
	int GetGCost() { return gCost; }
	int GetHCost() { return hCost; }
	sf::Vector2f GetWorldPos() { return worldPos; }
	sf::Vector2f GetSize() { return size; }
	void SetWorldPos(sf::Vector2f nextWorldPos) { worldPos = nextWorldPos; }
	void SetSize(sf::Vector2f nextSize) { size = nextSize; }
	// Neighbours 
	std::vector<Node*> neighboursOrth;
	Node* parent;
	// Calculate FGH values for pathfinding
	void CalculateFGH(Node*, Node*);
	// Shapes
	sf::RectangleShape tile;
	sf::CircleShape pellet;
	sf::CircleShape powerPellet;
	// Flags
	TileType type;
private:
	sf::Vector2f worldPos;
	sf::Vector2f size;
	// Pathfinding
	// fgh costs
	int fCost, gCost, hCost;
	// Calculate gCost, hCost, fCost
	int CalculateF();
	int CalculateG(Node*);
	int CalculateH(Node*);
};

