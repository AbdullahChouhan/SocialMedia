#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ResourceManager.hpp>

void ResourceManager::LoadTexture(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile("Resources/Textures/" + filename)) {
        throw std::runtime_error("Failed to load Texture: " + filename);
    }
    textures.emplace(filename, std::move(texture));
}
void ResourceManager::LoadSoundBuffer(const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Resources/Sounds/" + filename)) {
        throw std::runtime_error("Failed to load Sound: " + filename);
    }
    soundbuffers.emplace(filename, std::move(buffer));
}
void ResourceManager::LoadFont(const std::string& filename) {
    sf::Font font;
    if (!font.loadFromFile("Resources/Fonts/" + filename)) {
        throw std::runtime_error("Failed to load Font: " + filename);
    }
    fonts.emplace(filename, std::move(font));
}
sf::Sprite ResourceManager::CreateSprite(const std::string& filename, int ratio) {
    sf::Sprite sprite = sf::Sprite(textures[filename]);
    sprite.setScale(ratio, ratio);
    return sprite;
}
sf::Sound ResourceManager::CreateSound(const std::string& filename) {
    return sf::Sound(soundbuffers[filename]);
}
sf::Text ResourceManager::CreateText(const std::string& filename, int ratio) {
    sf::Text text = sf::Text();
    text.setFont(fonts[filename]);
    text.setCharacterSize(24 * ratio);
    return text;
}
void ResourceManager::UnloadTexture(const std::string& filename) {
    auto it = textures.find(filename);
    if (it != textures.end()) {
        textures.erase(it);
    }
}
void ResourceManager::UnloadSoundBuffer(const std::string& filename) {
    auto it = soundbuffers.find(filename);
    if (it != soundbuffers.end()) {
        soundbuffers.erase(it);
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
void ResourceManager::ClearSoundBuffers() {
    soundbuffers.clear();
}
void ResourceManager::ClearFonts() {
    fonts.clear();
}
void ResourceManager::ClearAll() {
    ClearTextures();
    ClearSoundBuffers();
    ClearFonts();
}