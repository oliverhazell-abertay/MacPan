#include "Application.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

void Application::Init(sf::RenderWindow* wind)
{
    window = wind;
    // Init grid
    InitGrid();
    // Init player -- TO BE MOVED TO PLAYER CLASS INIT
    player = new Player(sf::Vector2f(shapeWidth * 9, shapeHeight * 4), 
                            sf::Vector2f(shapeWidth * 0.97f, shapeHeight * 0.97f), 
                            80.0f);
    // Init blinky
    blinky = new Enemy(grid, player, &grid[17][9], 
                                sf::Vector2f(shapeWidth * 17, shapeHeight * 9), 
                                sf::Vector2f(shapeWidth * 0.97f, shapeHeight * 0.97f), 
                                sf::Color::Red, 80.0f);
    // Init pinky
    sf::Color Pink(255, 184, 255, 255);
    pinky = new Enemy(grid, player, &grid[1][9],
                        sf::Vector2f(shapeWidth * 1, shapeHeight * 9),
                        sf::Vector2f(shapeWidth * 0.97f, shapeHeight * 0.97f),
                        Pink, 80.0f);
    // Init inky
    inky = new Enemy(grid, player, &grid[17][1],
                        sf::Vector2f(shapeWidth * 17, shapeHeight * 1),
                        sf::Vector2f(shapeWidth * 0.97f, shapeHeight * 0.97f),
                        sf::Color::Cyan, 80.0f);
}

void Application::CleanUp()
{
    delete window;
    window = NULL;

    delete blinky;
    blinky = NULL;
}

int Application::Update(float dt)
{
    // Input
    Input(dt);

    // Update player current node
    sf::Vector2i playerGridPos = FindCurrentNode(*player);
    player->currentNode = &grid[playerGridPos.x][playerGridPos.y];
    // Update player neighbours for collision detection
    player->leftAdj = &grid[playerGridPos.x - 1][playerGridPos.y];
    player->rightAdj = &grid[playerGridPos.x + 1][playerGridPos.y];
    player->upAdj = &grid[playerGridPos.x][playerGridPos.y - 1];
    player->downAdj = &grid[playerGridPos.x][playerGridPos.y + 1];
    // Player update
    player->Update(dt);

    // Update blinky current node
    sf::Vector2i blinkyGridPos = FindCurrentNode(*blinky);
    blinky->currentNode = &grid[blinkyGridPos.x][blinkyGridPos.y];
    // Enemy update
    blinky->Update(dt);

    // Update pinky current node
    sf::Vector2i pinkyGridPos = FindCurrentNode(*pinky);
    pinky->currentNode = &grid[pinkyGridPos.x][pinkyGridPos.y];
    // Enemy update
    pinky->Update(dt);

    // Update inky current node
    sf::Vector2i inkyGridPos = FindCurrentNode(*inky);
    inky->currentNode = &grid[inkyGridPos.x][inkyGridPos.y];
    // Enemy update
    inky->Update(dt);

    // Collision detection
    if (player->currentNode == blinky->currentNode)
        std::cout << "Collision!\n";
    if (player->currentNode == pinky->currentNode)
        std::cout << "Collision!\n";

    // Render
    Render();

    return 0;
}

void Application::Input(float dt)
{
    window->setKeyRepeatEnabled(false);
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        // ESC - Close window
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();
        // WASD movement
        // Left arrow
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            // Check player can move in direction before setting
            if (player->leftAdj->type != TileType::obstacle && FuzzyEquals(player->position.y, player->currentNode->GetWorldPos().y, movementTolerance))
            {
                player->direction = sf::Vector2f(-1.0f, 0.0f);
                player->position = sf::Vector2f(player->position.x, player->leftAdj->gridPos.y * shapeHeight);
            }
        }
        // Right arrow
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // Check player can move in direction before setting
            if (player->rightAdj->type != TileType::obstacle && FuzzyEquals(player->position.y, player->currentNode->GetWorldPos().y, movementTolerance))
            {
                player->direction = sf::Vector2f(1.0f, 0.0f);
                player->position = sf::Vector2f(player->position.x, player->rightAdj->gridPos.y * shapeHeight);
            }
        }
        // Up arrow
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            // Check player can move in direction before setting
            if (player->upAdj->type != TileType::obstacle && FuzzyEquals(player->position.x, player->currentNode->GetWorldPos().x, movementTolerance))
            {
                player->direction = sf::Vector2f(0.0f, -1.0f);
                player->position = sf::Vector2f(player->upAdj->gridPos.x * shapeWidth, player->position.y);
            }
        }
        // Down arrow
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            // Check player can move in direction before setting
            if (player->downAdj->type != TileType::obstacle && FuzzyEquals(player->position.x, player->currentNode->GetWorldPos().x, movementTolerance))
            {
                player->direction = sf::Vector2f(0.0f, 1.0f);
                player->position = sf::Vector2f(player->downAdj->gridPos.x * shapeWidth, player->position.y);
            }
        }
    }

}

void Application::Render()
{
    window->clear();
    // Draw grid
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            grid[i][j].Render(window);
        }
    }
    // Draw player
    window->draw(player->shape);
    // Draw blinky
    window->draw(blinky->shape);
    // Draw pinky
    window->draw(pinky->shape);
    // Draw inky
    window->draw(inky->shape);

    // Display
    window->display();
}

void Application::InitGrid()
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            // Variables
            grid[i][j].Init(sf::Vector2f(i * shapeWidth, j * shapeHeight), sf::Vector2f(shapeWidth, shapeHeight), sf::Vector2i(i, j), TileType::pellet);
            // Neighbours - Only assign neighbour in direction if node
            //              is not on an edge
            //North
            if (j > 0)
                grid[i][j].neighboursOrth.push_back(&grid[i][j - 1]);
            // South
            if (j < GRID_HEIGHT - 1)
                grid[i][j].neighboursOrth.push_back(&grid[i][j + 1]);
            // East
            if (i < GRID_WIDTH - 1)
                grid[i][j].neighboursOrth.push_back(&grid[i + 1][j]);
            // West
            if (i > 0)
                grid[i][j].neighboursOrth.push_back(&grid[i - 1][j]);
        }
    }
    // Load each tile's type from file
    FileToGrid("level.txt");
}

void Application::FileToGrid(std::string filename)
{
    // For every line of file, take each number corresponding to
    // node in grid. Convert number to tile type and assign.
    std::fstream myFile(filename, std::ios_base::in);
    for (int j = 0; j < GRID_HEIGHT; j++)
    {
        // Read line
        std::string line;
        std::getline(myFile, line);
        // Convert line into tiles
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            int tempInt = line[i] - 48;
            grid[i][j].type = (TileType)tempInt;
        }
    }
    myFile.close();
}

bool Application::FuzzyEquals(float a, float b, float tolerance)
{
    return std::abs(a - b) <= tolerance;
}

bool Application::AABBCollision(sf::RectangleShape a, sf::RectangleShape b)
{
    sf::Vector2f aPos, bPos;
    sf::Vector2f aSize, bSize;
    aPos = a.getPosition();
    bPos = b.getPosition();
    aSize = a.getSize();
    bSize = b.getSize();

    // Return true if:
    return aPos.x < bPos.x + bSize.x // A's left side is left of B's right side
        && aPos.x + aSize.x > bPos.x // A's right side is right of B's left side
        && aPos.y < bPos.y + bSize.y // A's top is higher than B's bottom
        && aPos.y + aSize.y > bPos.y; // A's bottom is lower than B's top
}

sf::Vector2i Application::FindCurrentNode(GameObject gameObject)
{
    // Find the current grid square the game object occupies by dividing the world position
    // of the shape's centre by the shape size
    sf::Vector2i currentNodePos;
    currentNodePos.x = (int)(std::floor((gameObject.position.x + (shapeWidth * 0.5f)) / shapeWidth));
    currentNodePos.y = (int)(std::floor((gameObject.position.y + (shapeHeight * 0.5f)) / shapeHeight));
    return currentNodePos;
}