#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <nlohmann/json.hpp>

#include "ResourceManager.hpp"
#include "Animations.hpp"
#include "Input.hpp"
#include "AccountManager.hpp"

class App {
    private:
        App();
        float zoom = 1.f;
        ResourceManager rm = ResourceManager::GetInstance();
        AccountManager am = AccountManager::GetInstance();
        std::unordered_map<std::string, Animation*> animations;
        sf::RenderWindow window;
        std::unordered_map<std::string, sf::Text> texts;
        std::unordered_map<std::string, Button*> buttons;
        std::unordered_map<std::string, TextInputField*> textFields;
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
        void init();
        void end();
    public:
        static void Run();
};