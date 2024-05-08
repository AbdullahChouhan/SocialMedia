#include "headers/Animations.hpp"

Animation::Animation(sf::Texture& texture, std::string& filename, float speed, int loop, int active) {
    this->active = active;
    this->loop = loop;
    this->speed = speed;
    this->frame = 0;
    this->delay = 0;
    sprite.setTexture(texture);
    std::ifstream file("resources/animations/" + filename + ".json");
    if (file.is_open()) {
        json = nlohmann::json::parse(file);
        int MaxLeft = 0;
        for (auto& animation : json["animations"]) {
            for (int i = 0; i < animation["frames"]; i++) {
                frames.push_back(sf::IntRect(MaxLeft, 0, animation["w"], animation["h"]));
                MaxLeft = MaxLeft + int(animation["w"]);
            }
        }
        file.close();
    }
    else {
        std::cout << "Failed to open " << filename << ".json\n";
    }
}

void Animation::update(float speed, int active, int loop) {
    if (active != -1) {
        this->active = active;
    }
    if (loop != -1) {
        this->loop = loop;
    }
    if (speed != -1) {
        this->speed = speed;
    }
    if (active == 1 && speed > 0) {
        delay += speed;
        if (delay >= 1) {
            while (delay >= 1) {
                delay -= 1;
                frame = (frame + 1) % frames.size();
            }
            sprite.setTextureRect(frames[frame]);
            if (loop == 0 && frame >= frames.size() - 1) {
                active = 0;
            }
        }
    }   
}

FadeAnimation::FadeAnimation(sf::Texture& texture, std::string& filename, float speed, float inRatio, float outRatio, int loop, int active) : Animation(texture, filename, speed, loop, active) {
    if (inRatio + outRatio > 1) {
        throw std::runtime_error("FadeAnimation: inRatio + outRatio must be less than 1");
    }
    this->inRatio = inRatio;
    this->outRatio = outRatio;
    updateColour();
}
void FadeAnimation::updateColour() {
    float progress = static_cast<float>(frame) / frames.size();
    float alpha = 1.0f;
    if (progress < inRatio) {
        alpha = progress / inRatio;
    }
    else if (progress > 1.0f - outRatio) {
        alpha = (1.0f - progress) / outRatio;
    }
    sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha * 255)));
}

void FadeAnimation::update(float speed, int active, int loop) {
    Animation::update(speed, active, loop);
    updateColour();
}