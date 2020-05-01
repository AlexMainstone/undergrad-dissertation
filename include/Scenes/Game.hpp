#pragma once

#include <SFML/Graphics.hpp>
#include "World/Map.hpp"
#include "World/MapGenerator.hpp"

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
    float zoom;
};