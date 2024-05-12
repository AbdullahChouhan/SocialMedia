#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Post.hpp"
#include "User.hpp"

class Feed {
    private:
        Feed(User ActiveUser);
        User ActiveUser;
        std::vector<Post*> posts;
    public:
        static Feed& GetInstance(User ActiveUser);
        void populateFeed();
        void scrollFeed(sf::Event::MouseWheelScrollEvent event);
        void drawFeed(sf::RenderWindow& window);
};