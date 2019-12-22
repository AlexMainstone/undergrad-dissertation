#pragma once

#include <SFML/Graphics.hpp>
#include "World/City.hpp"

class Map
{
public:
    Map(sf::Texture texture, sf::VertexArray lines);

    void addCity(sf::Vector2f pos, const char *name, unsigned int power);
    void addLandMass(sf::ConvexShape shape);

    void draw(sf::RenderWindow &window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::VertexArray lines;

    std::vector<City> cities;
};