#include <World/Map.hpp>

Map::Map(sf::Texture texture, sf::VertexArray lines)
{
    this->texture = texture;
    sprite.setTexture(this->texture);
    this->lines = lines;
}

void Map::draw(sf::RenderWindow &window)
{
    // window.draw(sprite);
    window.draw(lines);
}