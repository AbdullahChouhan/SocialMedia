#pragma once

#include <vector>
#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>


class Animation {
    protected:
        sf::Sprite sprite;
        std::vector<sf::IntRect> frames;
        float speed, frameprogress, fadeprogress;
        int active, loop, frame;
    public:
        Animation(sf::Sprite sprite, const std::string& filename, float speed, int loop = 0, int active = 1, sf::Vector2f scale = sf::Vector2f(1, 1));
        virtual void update(float speed = -1, int active = -1, int loop = -1, sf::Vector2f scale = sf::Vector2f(-1, -1));
        sf::Sprite getSprite() const;
        void draw(sf::RenderWindow& window);
        float getSpeed() const;
        int getActive() const;
        void setActive(int active);
};

class FadeAnimation : public Animation {
    private:
        float inRatio, outRatio;
        void updateColour();
    public:
        FadeAnimation(sf::Sprite sprite, const std::string& filename, float speed, float inRatio, float outRatio, int loop = 0, int active = 1, sf::Vector2f scale = sf::Vector2f(1, 1));
        void update(float speed = -1, int active = -1, int loop = -1, sf::Vector2f scale = sf::Vector2f(-1, -1)) override;
};