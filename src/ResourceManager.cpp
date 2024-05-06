#include <ResourceManager.hpp>

ResourceManager::ResourceManager() {}

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::LoadTexture(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile("Resources/Textures/" + filename)) {
        throw std::runtime_error("Failed to load Texture: " + filename);
    }
    textures.emplace(filename, std::move(texture));
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
sf::Text ResourceManager::CreateText(const std::string& filename, int ratio) {
    sf::Text text = sf::Text();
    text.setFont(fonts[filename]);
    text.setCharacterSize(24 * ratio);
    return text;
}
void ResourceManager::AddPost(const std::string& id, const Post& post) {
    if (posts.find(id) == posts.end()) {
        posts.emplace(id, std::vector<Post>());
    }
}
void ResourceManager::RemovePost(const std::string& id) {
    auto it = posts.find(id);
    if (it != posts.end()) {
        posts.erase(it);
    }
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