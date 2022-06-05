#include "pathfinder.h"

void Pathfinder::Init(Node grid[GRID_WIDTH][GRID_HEIGHT])
{
    // Copy game grid for pathfinding
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            navGrid[i][j] = grid[i][j];
        }
    }
    // Re-Initialise grid to correct neighbour pointers
    ReInitGrid();
}

void Pathfinder::ReInitGrid()
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            // Clear neighbours pointing to game grid
            navGrid[i][j].neighboursOrth.clear();           
            // Neighbours - Only assign neighbour in direction if node
            //              is not on an edge
            //North
            if (j > 0)
                navGrid[i][j].neighboursOrth.push_back(&navGrid[i][j - 1]);
            // South
            if (j < GRID_HEIGHT - 1)
                navGrid[i][j].neighboursOrth.push_back(&navGrid[i][j + 1]);
            // East
            if (i < GRID_WIDTH - 1)
                navGrid[i][j].neighboursOrth.push_back(&navGrid[i + 1][j]);
            // West
            if (i > 0)
                navGrid[i][j].neighboursOrth.push_back(&navGrid[i - 1][j]);
        }
    }
}

void Pathfinder::Render(sf::RenderWindow* window)
{
    window->clear();
    // Draw grid
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            navGrid[i][j].Render(window);
        }
    }
    window->display();
}

void Pathfinder::FindPath()
{
    // Add start node to open
    openNodes.push_back(startNode);
    Node* currentNode = *openNodes.begin();
    bool pathFound = false;
    // Loop to find path
    while (!pathFound)
    {
        int lowestF = 1000000;
        // Find node with lowest f cost
        for (auto& it : openNodes)
        {
            // If f cost is lowest so far
            if (it->GetFCost() < lowestF)
            {
                currentNode = it;
                lowestF = it->GetFCost();
            }
            // If f cost is equal, check if h cost is lower
            else if (it->GetFCost() == lowestF && it->GetHCost() < currentNode->GetHCost())
            {
                currentNode = it;
                lowestF = it->GetFCost();
            }
        }
        // Remove lowest f node from open, add to closed
        if (std::find(openNodes.begin(), openNodes.end(), currentNode) != openNodes.end())
            openNodes.remove(currentNode);
        if (std::find(closedNodes.begin(), closedNodes.end(), currentNode) == closedNodes.end())
            closedNodes.push_back(currentNode);

        // If current node is the target node, path found
        if (currentNode == endNode)
            pathFound = true;
        // If not, carry on searching using lowest f node
        else
        {
            // Calculate distance to each neighbour node
            // Orthogonal neighbours
            for (auto& it : currentNode->neighboursOrth)
            {
                if (it == endNode)
                {
                    it->parent = currentNode;
                    pathFound = true;
                }
                // If neighbour isn't an obstacle or in closed
                else if (it->type != TileType::obstacle && std::find(closedNodes.begin(), closedNodes.end(), it) == closedNodes.end())
                {
                    // If neighbour isn't in open or new path to neighbour is shorter
                    if (std::find(openNodes.begin(), openNodes.end(), it) == openNodes.end() || (it->GetFCost() + 1) < it->GetFCost())
                    {
                        it->CalculateFGH(startNode, endNode);
                        it->parent = currentNode;
                        // If neighbour isn't in open, add it
                        if (std::find(openNodes.begin(), openNodes.end(), it) == openNodes.end())
                            openNodes.push_back(it);
                    }
                }
            }
        }
    }

    // Colour path
    currentNode = endNode;
    while (currentNode != startNode)
    {
        currentNode->type = TileType::blank;
        currentNode = currentNode->parent;
    }
}
