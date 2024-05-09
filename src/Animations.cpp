#include "headers/Animations.hpp"

Animation::Animation(sf::Sprite sprite, const std::string& filename, float speed, int loop, int active, sf::Vector2f scale) : sprite(sprite) {
    this->active = active;
    this->loop = loop;
    this->speed = speed;
    this->frame = 0;
    this->frameprogress = 0.0f;
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
    this->sprite.setScale(scale);
}

void Animation::update(float speed, int active, int loop, sf::Vector2f scale) {
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
    if (scale.x != -1.f && scale.y != -1.f) {
        sprite.setScale(scale);
    }
    if (this->active == 1 && this->speed > 0) {
        frameprogress += this->speed;
        if (frameprogress >= 1) {
            while (frameprogress >= 1) {
                frameprogress -= 1;
                frame = (frame + 1) % frames.size();
            }
            sprite.setTextureRect(frames[frame]);
            if (this->loop == 0 && frame >= frames.size() - 1) {
                this->speed = 0.0f;
            }
        }
    }   
}

void Animation::draw(sf::RenderWindow& window) {
    if (active == 1) {
        window.draw(sprite);
    }
}

float Animation::getSpeed() const {
    return speed;
}

int Animation::getActive() const {
    return active;
}

void Animation::setActive(int active) {
    this->active = active;
}

FadeAnimation::FadeAnimation(sf::Sprite sprite, const std::string& filename, float speed, float inRatio, float outRatio, int loop, int active, sf::Vector2f scale) : Animation(sprite, filename, speed, loop, active) {
    if (inRatio + outRatio > 1) {
        throw std::runtime_error("FadeAnimation: inRatio + outRatio must be less than or equal to 1");
    }
    this->inRatio = inRatio;
    this->outRatio = outRatio;
    updateColour();
}
void FadeAnimation::updateColour() {
    fadeprogress += speed;
    if (fadeprogress >= 1.0f)
        speed = 0.0f;
    float alpha = 1.0f;
    if (fadeprogress < inRatio) {
        alpha = fadeprogress / inRatio;
    }
    else if (fadeprogress > 1.0f - outRatio) {
        if (outRatio > 0)
            alpha = (1.0f - fadeprogress) / outRatio;
        if (alpha < 0)
            alpha = 0;
    }
    else 
        alpha = 1.0f;
    sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha * 255)));
}

void FadeAnimation::update(float speed, int active, int loop, sf::Vector2f scale) {
    if (speed != 0) {
        Animation::update(speed, active, loop, scale);
        updateColour();
    }
}