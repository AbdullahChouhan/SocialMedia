#include <ResourceManager.hpp>

ResourceManager::ResourceManager() {}

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::LoadTexture(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile("resources/Textures/" + filename + ".png")) {
        throw std::runtime_error("Failed to load Texture: " + filename + ".png");
    }
    textures.emplace(filename, std::move(texture));
}
void ResourceManager::LoadFont(const std::string& filename) {
    sf::Font font;
    if (!font.loadFromFile("resources/Fonts/" + filename + ".ttf")) {
        throw std::runtime_error("Failed to load Font: " + filename + ".ttf");
    }
    fonts.emplace(filename, std::move(font));
}
sf::Sprite ResourceManager::CreateSprite(const std::string& filename, int ratio) {
    sf::Sprite sprite = sf::Sprite(textures[filename]);
    sprite.setScale(ratio, ratio);
    return sprite;
}
sf::Text ResourceManager::CreateText(std::string displayText, sf::Vector2f position , const std::string& filename, int ratio) {
    sf::Text text = sf::Text();
    text.setString(displayText);
    text.setFont(fonts[filename]);
    text.setCharacterSize(24 * ratio);
    text.setPosition(position);
    text.setFillColor(sf::Color::White);
    return text;
}
void ResourceManager::UnloadTexture(const std::string& filename) {
    auto it = textures.find(filename);
    if (it != textures.end()) {
        textures.erase(it);
    }
}
void ResourceManager::UnloadFont(const std::string& filename) {
    auto it = fonts.find(filename);
    if (it != fonts.end()) {
        fonts.erase(it);
    }
}
void ResourceManager::ClearTextures() {
    textures.clear();
}
void ResourceManager::ClearFonts() {
    fonts.clear();
}
void ResourceManager::ClearAll() {
    ClearTextures();
    ClearFonts();
}