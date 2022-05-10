#include <iostream>
#include <SFML/Graphics.hpp>
#include "application.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NotPacMan");
    window.setFramerateLimit(60);

    Application application;
    application.Init(&window);

    while (window.isOpen())
    {
        application.Update();
    }

    return 0;
}