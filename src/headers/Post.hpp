#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Post {
    private:
        std::string* ownderId;
        std::string title, content;
        std::tm date;
        int likes;
        // std::vector<std::Comment> comments;
        std::vector<std::string*> likedBy;
        std::vector<sf::Texture> textures;
    public:
        Post() = default;
        Post(std::string* id, std::string title, std::string content);
        void AddLike(std::string* id);
        void RemoveLike(std::string* id);
        void AddTexture(sf::Texture texture);
        void RemoveTexture(int index);
        // Delete should be called in the app class
};