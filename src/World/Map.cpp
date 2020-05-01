#include <World/Map.hpp>
#include <math.h>

Map::Map(sf::Texture texture, sf::VertexArray lines)
{
    this->texture = texture;
    sprite.setTexture(this->texture);
    this->lines = lines;

    text.setColor(sf::Color::Black);
    citydot.setOutlineColor(sf::Color::Black);
    citydot.setFillColor(sf::Color::White);
    citydot.setOutlineThickness(2.0f);
    citydot.setRadius(5);
    citydot.setOrigin(5, 5);

    font.loadFromFile("../res/fonts/ferrum.otf");
    text.setFont(font);

    mountainTexture.loadFromFile("../res/images/mountain.png");
}

void Map::update(float dt)
{
}

void Map::handleEvent(sf::Event e) {
    if(e.type == sf::Event::MouseMoved) {
        sf::Vector2f pos = sf::Vector2f(e.mouseMove.x, e.mouseMove.y);
        for(int i = 0; i < cities.size(); i++) {
            if(std::sqrt(std::pow(pos.x - cities[i].pos.x, 2) + std::pow(pos.y - cities[i].pos.y, 2)) < 5) {
                cities[i].drawName = true;
            } else {
                cities[i].drawName = false;
            }
        }
    }
}

void Map::drawMountain(sf::Vector2f pos, sf::RenderWindow &window) {
    sf::Sprite mountain;
    mountain.setTexture(mountainTexture);
    mountain.setOrigin(mountain.getGlobalBounds().width/2, mountain.getGlobalBounds().height/2);
    mountain.setScale(0.02, 0.02);
    mountain.setPosition(pos);
    window.draw(mountain);
}

void Map::drawTrees(sf::Vector2f pos, sf::RenderWindow &window) {
    sf::CircleShape triangle(2);
    triangle.setPosition(pos);
    triangle.setOutlineColor(sf::Color::Black);
    triangle.setOutlineThickness(1);
    window.draw(triangle);
}

void Map::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
    //window.draw(sprite);
    window.draw(lines);

    for (auto t : trees) {
        drawTrees(t, window);
    }

    for(auto m : mountains) {
        drawMountain(m, window);
    }

    for (auto c : cities)
    {
        text.setPosition(c.pos.x + 10, c.pos.y - 22);
        citydot.setPosition(c.pos);
        text.setString(c.name);
        window.draw(text);
        // if(c.drawName) {window.draw(text);}
        window.draw(citydot);
    }
}