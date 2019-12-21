#include <World/Map.hpp>

Map::Map(sf::Texture texture)
{
    this->texture = texture;
    sprite.setTexture(this->texture);
}

void Map::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}