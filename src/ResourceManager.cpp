#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <headers/ResourceManager.hpp>

class ResourceManager {
    private:
        std::unordered_map<std::string, sf::Texture> textures;
        std::unordered_map<std::string, sf::SoundBuffer> soundbuffers;
        std::unordered_map<std::string, sf::Font> fonts;
    public:
        void LoadTexture(const std::string& filename) {
            sf::Texture texture;
            if (!texture.loadFromFile("Resources/Textures/" + filename)) {
                throw std::runtime_error("Failed to load Texture: " + filename);
            }
            textures.emplace(filename, std::move(texture));
        }
        void LoadSoundBuffer(const std::string& filename) {
            sf::SoundBuffer buffer;
            if (!buffer.loadFromFile("Resources/Sounds/" + filename)) {
                throw std::runtime_error("Failed to load Sound: " + filename);
            }
            soundbuffers.emplace(filename, std::move(buffer));
        }
        void LoadFont(const std::string& filename) {
            sf::Font font;
            if (!font.loadFromFile("Resources/Fonts/" + filename)) {
                throw std::runtime_error("Failed to load Font: " + filename);
            }
            fonts.emplace(filename, std::move(font));
        }
        sf::Sprite CreateSprite(const std::string& filename, int ratio = 1) {
            sf::Sprite sprite = sf::Sprite(textures[filename]);
            sprite.setScale(ratio, ratio);
            return sprite;
        }
        sf::Sound CreateSound(const std::string& filename) {
            return sf::Sound(soundbuffers[filename]);
        }
        sf::Text CreateText(const std::string& filename, int ratio = 1) {
            sf::Text text = sf::Text();
            text.setFont(fonts[filename]);
            text.setCharacterSize(24 * ratio);
            return text;
        }
        void UnloadTexture(const std::string& filename) {
            auto it = textures.find(filename);
            if (it != textures.end()) {
                textures.erase(it);
            }
        }
        void UnloadSoundBuffer(const std::string& filename) {
            auto it = soundbuffers.find(filename);
            if (it != soundbuffers.end()) {
                soundbuffers.erase(it);
            }
        }
        void UnloadFont(const std::string& filename) {
            auto it = fonts.find(filename);
            if (it != fonts.end()) {
                fonts.erase(it);
            }
        }
        void ClearTextures() {
            textures.clear();
        }
        void ClearSoundBuffers() {
            soundbuffers.clear();
        }
        void ClearFonts() {
            fonts.clear();
        }
        void ClearAll() {
            ClearTextures();
            ClearSoundBuffers();
            ClearFonts();
        }
};