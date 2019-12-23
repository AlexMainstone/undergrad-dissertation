#pragma once

#include <SFML/Graphics.hpp>

struct City {
    sf::Vector2f pos;
    std::string name;
    City(sf::Vector2f pos, std::string name) : pos(pos), name(name) {}
};

class Map
{
public:
    Map(sf::Texture texture, sf::VertexArray lines);

    void addCity(City city) {cities.push_back(city);}
    void addLandMass(sf::ConvexShape shape);

    void update(float dt);

    void draw(sf::RenderWindow &window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::VertexArray lines;

    // Font loading
    sf::Font font;
    sf::Text text;
    sf::CircleShape citydot;


    std::vector<City> cities;
};