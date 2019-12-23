#include <World/Map.hpp>


Map::Map(sf::Texture texture, sf::VertexArray lines)
{
    this->texture = texture;
    sprite.setTexture(this->texture);
    this->lines = lines;


    text.setColor(sf::Color::Black);
    citydot.setFillColor(sf::Color::White);
    citydot.setOutlineColor(sf::Color::Black);
    citydot.setOutlineThickness(2.0f);
    citydot.setRadius(5);
    citydot.setOrigin(5, 5);

    font.loadFromFile("../res/fonts/ferrum.otf");
    text.setFont(font);
}


void Map::update(float dt) {

}

void Map::draw(sf::RenderWindow &window)
{
    // window.draw(sprite);
    window.draw(sprite);
    window.draw(lines);

    for(auto c : cities) {
        text.setPosition(c.pos.x + 10, c.pos.y-22);
        citydot.setPosition(c.pos);
        text.setString(c.name);
        window.draw(text);
        window.draw(citydot);
    }
}