#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceManager.hpp"

class App {
    private:
        App();
        sf::RenderWindow window;
        int ratio, height, width;
        bool isFullScreen;
        const int MinWidth = 1920, MinHeight = 1080;
        const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        void handleEvents();
        void toggleFullScreen();
        void update();
        void render();
    public:
        static void Run();
};