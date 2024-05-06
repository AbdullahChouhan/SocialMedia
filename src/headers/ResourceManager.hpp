#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager {
    private:
        ResourceManager();
        std::unordered_map<std::string, sf::Texture> textures;
        std::unordered_map<std::string, sf::SoundBuffer> soundbuffers;
        std::unordered_map<std::string, sf::Font> fonts;
    public:
        static ResourceManager& GetInstance();
        void LoadTexture(const std::string& filename);
        void LoadSoundBuffer(const std::string& filename);
        void LoadFont(const std::string& filename);
        sf::Sprite CreateSprite(const std::string& filename, int ratio = 1);
        sf::Sound CreateSound(const std::string& filename);
        sf::Text CreateText(const std::string& filename, int ratio = 1);
        void UnloadTexture(const std::string& filename);
        void UnloadSoundBuffer(const std::string& filename);
        void UnloadFont(const std::string& filename);
        void ClearTextures();
        void ClearSoundBuffers();
        void ClearFonts();
        void ClearAll();
};