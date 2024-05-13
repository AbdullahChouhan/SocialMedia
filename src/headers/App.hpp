#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <nlohmann/json.hpp>

#include "ResourceManager.hpp"
#include "Animations.hpp"
#include "Input.hpp"
#include "AccountManager.hpp"
#include "User.hpp"
#include "Feed.hpp"

class App {
    private:
        App();
        float zoom = 1.f;
        ResourceManager rm = ResourceManager::GetInstance();
        AccountManager am = AccountManager::GetInstance();
        Feed feed;
        nlohmann::json json;
        std::unordered_map<std::string, User*> users;
        sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(1920, 1080));
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
        void populateUsers();
        void startFeed();
        void handleEvents();
        void toggleFullScreen();
        void update();
        void render();
        void init();
        void end();
    public:
        static void Run();
};