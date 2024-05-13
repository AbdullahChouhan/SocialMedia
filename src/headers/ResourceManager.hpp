#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager {
    private:
        ResourceManager();
        std::unordered_map<std::string, sf::Texture> textures;
        std::unordered_map<std::string, sf::Font> fonts;
    public:
        static ResourceManager& GetInstance();
        void LoadTexture(const std::string& filename);
        void LoadSoundBuffer(const std::string& filename);
        void LoadFont(const std::string& filename);
        sf::Sprite CreateSprite(const std::string& filename, int ratio = 1);
        sf::Text CreateText(std::string displayText, sf::Vector2f position = sf::Vector2f(0.f, 0.f), const std::string& filename = "OpenSans", int ratio = 1);
        void UnloadTexture(const std::string& filename);
        void UnloadFont(const std::string& filename);
        void ClearTextures();
        void ClearFonts();
        void ClearAll();
};