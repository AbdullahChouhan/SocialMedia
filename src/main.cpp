#include <array>
#include <chrono>
#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ResourceManager.hpp>

int main()
{
    ResourceManager rm;
    int ratio;
    bool isFullScreen = false;

    

    const int MinWidth = 18, MinHeight = 41;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    if (desktop.width > desktop.height)
        ratio = desktop.height / MinHeight;
    else
        ratio = desktop.width / MinWidth;

    int height = MinHeight * ratio, width = MinWidth * ratio;

    sf::RenderWindow window(sf::VideoMode(width, height), "Totally Original Social Media App", sf::Style::Close);
    window.setPosition(sf::Vector2i(window.getPosition().x, 0));
    window.setFramerateLimit(60);

    //Loop
    while (window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {

            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
            {
                if (!isFullScreen) {
                    window.create(desktop, "Totally Original Social Media App", sf::Style::Fullscreen);
                }
                else {
                    window.create(sf::VideoMode(width, height), "Totally Original Social Media App", sf::Style::Close);
                    window.setPosition(sf::Vector2i(window.getPosition().x, 0));
                }
                isFullScreen = !isFullScreen;
                window.setFramerateLimit(60);
            }
        }

        if (1) {
            window.clear();
            window.draw(sf::Sprite(rm.CreateSprite("Totally Original Social Media App"))); //Example
            window.display();
        }
    }
}