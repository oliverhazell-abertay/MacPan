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
    player.position = sf::Vector2f(shapeWidth, shapeHeight);
    player.direction = sf::Vector2f(0.0f, 0.0f);    // Start player moving right
    player.shape.setPosition(player.position);
    player.shape.setSize(sf::Vector2f(shapeWidth * 0.97f, shapeHeight * 0.97f));
    player.shape.setFillColor(sf::Color::Yellow);
    player.shape.setOutlineColor(sf::Color::Black);
    player.shape.setOutlineThickness(0.0f);
    // Init enemy -- TO BE MOVED TO ENEMY CLASS INIT
    blinky.Init(grid, &player);
    blinky.position = sf::Vector2f(shapeWidth * 17, shapeHeight * 9);
    blinky.shape.setPosition(blinky.position);
    blinky.shape.setSize(sf::Vector2f(shapeWidth * 0.97f, shapeHeight * 0.97f));
    blinky.shape.setFillColor(sf::Color::Red);
    blinky.shape.setOutlineColor(sf::Color::Black);
    blinky.shape.setOutlineThickness(0.0f);
    blinky.direction = sf::Vector2f(-1.0f, 0.0f);
    // Init enemy -- TO BE MOVED TO ENEMY CLASS INIT
    pinky.Init(grid, &player);
    pinky.position = sf::Vector2f(shapeWidth * 1, shapeHeight * 9);
    pinky.shape.setPosition(pinky.position);
    pinky.shape.setSize(sf::Vector2f(shapeWidth * 0.97f, shapeHeight * 0.97f));
    sf::Color Pink(255, 184, 255, 255);
    pinky.shape.setFillColor(Pink);
    pinky.shape.setOutlineColor(sf::Color::Black);
    pinky.shape.setOutlineThickness(0.0f);
    pinky.direction = sf::Vector2f(-1.0f, 0.0f);
}

void Application::CleanUp()
{
    delete window;
    window = NULL;
}

int Application::Update()
{

    while (window->isOpen())
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
                if (player.leftAdj->type != TileType::obstacle && FuzzyEquals(player.position.y, player.currentNode->GetWorldPos().y, movementTolerance))
                {
                    player.direction = sf::Vector2f(-1.0f, 0.0f);
                    player.position = sf::Vector2f(player.position.x, player.leftAdj->gridPos.y * shapeHeight);
                }
            } 
            // Right arrow
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                // Check player can move in direction before setting
                if (player.rightAdj->type != TileType::obstacle && FuzzyEquals(player.position.y, player.currentNode->GetWorldPos().y, movementTolerance))
                {
                    player.direction = sf::Vector2f(1.0f, 0.0f);
                    player.position = sf::Vector2f(player.position.x, player.rightAdj->gridPos.y * shapeHeight);
                }
            }
            // Up arrow
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                // Check player can move in direction before setting
                if (player.upAdj->type != TileType::obstacle && FuzzyEquals(player.position.x, player.currentNode->GetWorldPos().x, movementTolerance))
                {
                    player.direction = sf::Vector2f(0.0f, -1.0f);
                    player.position = sf::Vector2f(player.upAdj->gridPos.x * shapeWidth, player.position.y);
                }
            }
            // Down arrow
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                // Check player can move in direction before setting
                if (player.downAdj->type != TileType::obstacle && FuzzyEquals(player.position.x, player.currentNode->GetWorldPos().x, movementTolerance))
                {
                    player.direction = sf::Vector2f(0.0f, 1.0f);
                    player.position = sf::Vector2f(player.downAdj->gridPos.x * shapeWidth, player.position.y);
                }
            }
        }
        // Update player position if player is moving
        sf::Vector2f tempPos = player.position;
        tempPos.x = player.position.x + (player.direction.x * playerSpeed);
        tempPos.y = player.position.y + (player.direction.y * playerSpeed);
        player.position = tempPos;
        // Update player current node
        player.currentNode = &grid[(int)(std::floor((tempPos.x + (shapeWidth * 0.5f)) / shapeWidth))][(int)(std::floor((tempPos.y + (shapeHeight * 0.5f)) / shapeHeight))];
        // Update player neighbours
        player.leftAdj = &grid[player.currentNode->gridPos.x - 1][player.currentNode->gridPos.y];
        player.rightAdj = &grid[player.currentNode->gridPos.x + 1][player.currentNode->gridPos.y];
        player.upAdj = &grid[player.currentNode->gridPos.x][player.currentNode->gridPos.y - 1];
        player.downAdj = &grid[player.currentNode->gridPos.x][player.currentNode->gridPos.y + 1];
        // Player update
        player.Update();

        // Update enemy position -- TO ME MOVED TO ENEMY CLASS
        tempPos = blinky.position;
        tempPos.x = blinky.position.x + (blinky.direction.x * playerSpeed);
        tempPos.y = blinky.position.y + (blinky.direction.y * playerSpeed);
        blinky.position = tempPos;
        // Update blinky current node
        blinky.currentNode = &grid[(int)(std::floor((tempPos.x + (shapeWidth * 0.5f)) / shapeWidth))][(int)(std::floor((tempPos.y + (shapeHeight * 0.5f)) / shapeHeight))];
         // Update blinky neighbours
        blinky.leftAdj = &grid[blinky.currentNode->gridPos.x - 1][blinky.currentNode->gridPos.y];
        blinky.rightAdj = &grid[blinky.currentNode->gridPos.x + 1][blinky.currentNode->gridPos.y];
        blinky.upAdj = &grid[blinky.currentNode->gridPos.x][blinky.currentNode->gridPos.y - 1];
        blinky.downAdj = &grid[blinky.currentNode->gridPos.x][blinky.currentNode->gridPos.y + 1];
        // Enemy update
        blinky.Update();

        // Update enemy position -- TO ME MOVED TO ENEMY CLASS
        tempPos = pinky.position;
        tempPos.x = pinky.position.x + (pinky.direction.x * playerSpeed);
        tempPos.y = pinky.position.y + (pinky.direction.y * playerSpeed);
        pinky.position = tempPos;
        // Update pinky current node
        pinky.currentNode = &grid[(int)(std::floor((tempPos.x + (shapeWidth * 0.5f)) / shapeWidth))][(int)(std::floor((tempPos.y + (shapeHeight * 0.5f)) / shapeHeight))];
        // Update pinky neighbours
        pinky.leftAdj = &grid[pinky.currentNode->gridPos.x - 1][pinky.currentNode->gridPos.y];
        pinky.rightAdj = &grid[pinky.currentNode->gridPos.x + 1][pinky.currentNode->gridPos.y];
        pinky.upAdj = &grid[pinky.currentNode->gridPos.x][pinky.currentNode->gridPos.y - 1];
        pinky.downAdj = &grid[pinky.currentNode->gridPos.x][pinky.currentNode->gridPos.y + 1];
        // Enemy update
        pinky.Update();

        // Collision detection
        if (AABBCollision(player.shape, pinky.shape))
            std::cout << "Collision!\n";

        // Render
        Render();
    }

    return 0;
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
    window->draw(player.shape);
    window->draw(blinky.shape);
    window->draw(pinky.shape);
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
        std::string line;
        std::getline(myFile, line);

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