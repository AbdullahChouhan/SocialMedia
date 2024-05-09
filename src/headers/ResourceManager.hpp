#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Post.hpp"

class ResourceManager {
    private:
        ResourceManager();
        std::unordered_map<std::string, sf::Texture> textures;
        std::unordered_map<std::string, sf::Font> fonts;
        std::unordered_map<std::string, std::vector<Post>> posts;
    public:
        static ResourceManager& GetInstance();
        void LoadTexture(const std::string& filename);
        void LoadSoundBuffer(const std::string& filename);
        void LoadFont(const std::string& filename);
        sf::Sprite CreateSprite(const std::string& filename, int ratio = 1);
        sf::Text CreateText(const std::string& filename, int ratio = 1);
        void AddPost(const std::string& id, const Post& post);
        void RemovePost(const std::string& id);
        void UnloadTexture(const std::string& filename);
        void UnloadFont(const std::string& filename);
        void ClearTextures();
        void ClearFonts();
        void ClearAll();
};