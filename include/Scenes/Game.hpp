#pragma once

#include <SFML/Graphics.hpp>
#include "World/Map.hpp"

class Game
{
public:
    Game(sf::RenderWindow &window);

    void handleEvent(sf::Event &e);
    void update(float dt);
    void render();

private:
    sf::RenderWindow &window;
    Map *map;
};