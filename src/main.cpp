#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "window");
    
    sf::CircleShape circle1(10.f);
    sf::CircleShape circle2(10.f);
    circle2.setPosition(window.getSize().x-10, window.getSize().y-10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.draw(circle1);
        window.draw(circle2);
        window.display();
    }
}