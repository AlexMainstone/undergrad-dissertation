#include <SFML/Graphics.hpp>
#include "Scenes/Game.hpp"

int main()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "dissertation-project");

    // TODO create abstract scene class for switching
    Game *game = new Game(window);

    // Delta time clock
    sf::Clock dt;

    // Game loop
    while (window.isOpen())
    {
        // Handle Events
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            // Pass event to scene
            game->handleEvent(e);
        }

        // Update
        game->update(dt.restart().asSeconds());

        // Render
        window.clear();

        // Render scene
        game->render();

        window.display();
    }
}