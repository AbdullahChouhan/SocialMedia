#include "headers/App.hpp"

App::App() : isFullScreen(false) {
    scale.y = desktop.height / MinHeight;
    scale.x = desktop.width / MinWidth;

    height = MinHeight * scale.y;
    width = MinWidth * scale.x;

    window.create(sf::VideoMode(width, height), "Totally Original Social Media App", sf::Style::Close);
    if (desktop.width == 1920 && desktop.height == 1080)
        window.setPosition(sf::Vector2i(0, 0));
    else
        window.setPosition(sf::Vector2i(window.getPosition().x, 0));
    window.setFramerateLimit(60);
}

void App::toggleFullScreen() {
    if (!isFullScreen) {
        window.create(desktop, "Totally Original Social Media App", sf::Style::Fullscreen);
    }
    else {
        window.create(sf::VideoMode(width, height), "Totally Original Social Media App", sf::Style::Close);
        if (desktop.width == 1920 && desktop.height == 1080)
            window.setPosition(sf::Vector2i(0, 0));
        else
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
    if (state == AppState::Login) {
        if (animations["login1"]->getActive()) {
            animations["login1"]->update();
            if (animations["login1"]->getSpeed() == 0.f) {
                animations["login1"]->setActive(0);
                rm.UnloadTexture("login1");
                animations["login2"]->setActive(1);
            }
        }
        if (animations["login2"]->getActive()) {
            animations["login2"]->update();
        }
    }
}

void App::render() {
    window.clear();
    switch (state)
    {
    case AppState::Login:
        animations["login1"]->draw(window);
        animations["login2"]->draw(window);
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
    app.rm.LoadTexture("login1");
    app.rm.LoadTexture("login2");
    app.animations["login1"] = new Animation(app.rm.CreateSprite("login1"), "login1", 0.2f, 0, 1, sf::Vector2f(2.4f, 2.25f));
    app.animations["login2"] = new Animation(app.rm.CreateSprite("login2"), "login2", 0.2f, 0, 0, sf::Vector2f(2.4f, 2.25f));
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