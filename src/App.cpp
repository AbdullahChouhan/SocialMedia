#include "headers/App.hpp"

#include <SFML/Graphics.hpp>

App::App() : isFullScreen(false) {
    if (desktop.width > desktop.height)
        ratio = desktop.height / MinHeight;
    else
        ratio = desktop.width / MinWidth;

    height = MinHeight * ratio;
    width = MinWidth * ratio;

    window.create(sf::VideoMode(width, height), "Totally Original Social Media App", sf::Style::Close);
    window.setPosition(sf::Vector2i(window.getPosition().x, 0));
    window.setFramerateLimit(60);
}

void App::toggleFullScreen() {
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

void App::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
        {
            toggleFullScreen();
        }
    }
}

void App::update() {
    //Update
}

void App::render() {
    window.clear();
    //window.draw();
    window.display();
}

void App::Run() {
    static App app;
    ResourceManager rm = ResourceManager::GetInstance();
    while (app.window.isOpen())
    {
        app.handleEvents();
        app.update();
        if (1) {
            app.render();
        }
    }
}