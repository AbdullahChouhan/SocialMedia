#include "headers/Animations.hpp"

Animation::Animation(const sf::Sprite sprite, const std::string& filename, float speed, int loop, int active) : sprite(sprite) {
    this->active = active;
    this->loop = loop;
    this->speed = speed;
    this->frame = 0;
    this->progress = 0.0f;
    std::ifstream file("resources/AnimationData/" + filename + ".json");
    if (file.is_open()) {
        nlohmann::json json = nlohmann::json::parse(file);
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
    if (speed == 0) {
        return;
    }
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
        progress += speed;
        if (progress >= 1) {
            while (progress >= 1) {
                progress -= 1;
                frame = (frame + 1) % frames.size();
            }
            sprite.setTextureRect(frames[frame]);
            if (loop == 0 && frame >= frames.size() - 1) {
                speed = 0.0f;
            }
        }
    }   
}

sf::Sprite Animation::getSprite() const {
    return sprite;
}

FadeAnimation::FadeAnimation(const sf::Sprite sprite, const std::string& filename, float speed, float inRatio, float outRatio, int loop, int active) : Animation(sprite, filename, speed, loop, active) {
    if (inRatio + outRatio > 1) {
        throw std::runtime_error("FadeAnimation: inRatio + outRatio must be less than or equal to 1");
    }
    this->inRatio = inRatio;
    this->outRatio = outRatio;
    updateColour();
}
void FadeAnimation::updateColour() {
    progress += speed;
    if (progress >= 1.0f)
        speed = 0.0f;
    float alpha = 1.0f;
    if (progress < inRatio) {
        alpha = progress / inRatio;
    }
    else if (progress > 1.0f - outRatio) {
        if (outRatio > 0)
            alpha = (1.0f - progress) / outRatio;
        if (alpha < 0)
            alpha = 0;
    }
    else 
        alpha = 1.0f;
    sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha * 255)));
}

void FadeAnimation::update(float speed, int active, int loop) {
    if (speed != 0) {
        Animation::update(speed, active, loop);
        updateColour();
    }
}