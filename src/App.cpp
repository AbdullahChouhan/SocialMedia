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
    animations["login"]->update();
}

void App::render() {
    window.clear();
    switch (state)
    {
    case AppState::Login:
        window.draw(animations["login"]->getSprite());
        break;
    case AppState::Feed:

        break;
    case AppState::Settings:

        break;
    default:
        break;
    }
    window.display();
}

void App::Run() {
    static App app;
    app.rm.LoadTexture("login");
    app.animations["login"] = new FadeAnimation(app.rm.CreateSprite("login"), "login", 0.01f, 1.0f, 0.0f);
    while (app.window.isOpen())
    {
        app.handleEvents();
        app.update();
        app.render();
    }
    for (auto& animation : app.animations) {
        delete animation.second;
    };
    app.rm.ClearAll();
}