#pragma once

#include<SFML/Graphics.hpp>
#include "World/City.hpp"

class Map
{
public:
    Map(sf::Texture texture);

    void addCity(sf::Vector2f pos, const char *name, unsigned int power);

    void draw(sf::RenderWindow &window);

private:
    sf::Texture texture;
    sf::Sprite sprite;

    std::vector<City> cities;
};