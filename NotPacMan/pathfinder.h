#pragma once
#include "node.h"
#include <list>
#define GRID_WIDTH 19
#define GRID_HEIGHT 11

class Pathfinder
{
public:
	void Init(Node[GRID_WIDTH][GRID_HEIGHT]);
	void Render(sf::RenderWindow*);
	void ReInitGrid();

	// Pathfinding
	void FindPath();
	Node navGrid[GRID_WIDTH][GRID_HEIGHT];
	std::vector<Node*> path;
	std::list<Node*> openNodes;
	std::list<Node*> closedNodes;
	
	// Take node from other grid and convert to equivalent node on navGrid
	void SetStart(Node* start) { startNode = &navGrid[start->gridPos.x][start->gridPos.y]; }
	void SetEnd(Node* end) { endNode = &navGrid[end->gridPos.x][end->gridPos.y]; };

private:
	Node* startNode;
	Node* endNode;
};

