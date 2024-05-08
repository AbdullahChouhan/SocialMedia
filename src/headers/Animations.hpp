#pragma once

#include <vector>
#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>


class Animation {
    private:
        nlohmann::json json;
    protected:
        sf::Sprite sprite;
        std::vector<sf::IntRect> frames;
        float speed;
        int active, loop, frame;
        float progress = 0.0f;
    public:
        Animation(const sf::Sprite sprite, const std::string& filename, float speed, int loop = 0, int active = 1);
        virtual void update(float speed = -1, int active = -1, int loop = -1);
        sf::Sprite getSprite() const;
};

class FadeAnimation : public Animation {
    private:
        float inRatio, outRatio;
        void updateColour();
    public:
        FadeAnimation(const sf::Sprite sprite, const std::string& filename, float speed, float inRatio, float outRatio, int loop = 0, int active = 1);
        void update(float speed = -1, int active = -1, int loop = -1) override;
};