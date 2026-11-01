#include <SFML/Graphics.hpp>
#include "renderer.hpp"

using namespace std;

int main() {
    unsigned int w = 1200, h = 800;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(w, h)), "Ponger");
    window.setFramerateLimit(600.0f);
    renderer ren(w, h, 3, 20, 200, 100, 1100);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }
        
        if (!ren.getIsEnd()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) ren.movePlayerUp();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) ren.movePlayerDown();
        }

        ren.update(window);
    }

    return 0;
}