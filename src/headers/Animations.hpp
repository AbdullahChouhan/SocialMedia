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
        int active, loop, frame, delay;
    public:
        Animation(sf::Texture& texture, std::string& filename, float speed, int loop = 0, int active = 1);
        virtual void update(float speed = -1, int active = -1, int loop = -1);
};

class FadeAnimation : public Animation {
    private:
        float inRatio, outRatio;
        void updateColour();
    public:
        FadeAnimation(sf::Texture& texture, std::string& filename, float speed, float inRatio, float outRatio, int loop = 0, int active = 1);
        void update(float speed = -1, int active = -1, int loop = -1) override;
};