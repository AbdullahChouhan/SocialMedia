#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <nlohmann/json.hpp>

#include "ResourceManager.hpp"
#include "Animations.hpp"

class App {
    private:
        App();
        ResourceManager rm = ResourceManager::GetInstance();
        std::unordered_map<std::string, Animation*> animations;
        sf::RenderWindow window;
        int height, width;
        sf::Vector2f scale;
        bool isFullScreen;
        const int MinWidth = 1920, MinHeight = 1080;
        const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        enum class AppState {Login, Feed, Settings};
        AppState state;
        void handleEvents();
        void toggleFullScreen();
        void update();
        void render();
    public:
        static void Run();
};