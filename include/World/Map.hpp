#pragma once

#include <SFML/Graphics.hpp>

struct City
{
    sf::Vector2f pos;
    std::string name;
    bool drawName;
    City(sf::Vector2f pos, std::string name) : pos(pos), name(name) { drawName = true; }
};

class Map
{
public:
    Map(sf::Texture texture, sf::VertexArray lines);

    void addCity(City city) { cities.push_back(city); }
    void addLandMass(sf::ConvexShape shape);
    
    void addMountain(sf::Vector2f pos) { mountains.push_back(pos); }
    std::size_t getMountainSize() { mountains.size(); }
    sf::Vector2f getMountain(int i) { return mountains[i]; }

    void addTrees(sf::Vector2f pos) { trees.push_back(pos); }

    void update(float dt);
    void handleEvent(sf::Event e);

    void draw(sf::RenderWindow &window);

private:
    void drawMountain(sf::Vector2f pos, sf::RenderWindow &window);
    void drawTrees(sf::Vector2f pos, sf::RenderWindow &window);
    
    sf::Texture texture;
    sf::Sprite sprite;
    sf::VertexArray lines;

    sf::Texture mountainTexture;

    // Font loading
    sf::Font font;
    sf::Text text;
    sf::CircleShape citydot;

    std::vector<City> cities;
    std::vector<sf::Vector2f> mountains;
    std::vector<sf::Vector2f> trees;
};