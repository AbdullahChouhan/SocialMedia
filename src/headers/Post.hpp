#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "ResourceManager.hpp"
#include "Input.hpp"
#include "Comment.hpp"

class Post {
    private:
        friend class Feed;
        ResourceManager rm = ResourceManager::GetInstance();
        Button likeButton;
        Button viewComments;
        std::string ownername, activityvalue;
        sf::Text title, content;
        std::time_t date;
        int likes;
        std::vector<Comment> comments;
        std::vector<std::string> likedBy;
    public:
        enum Activity {none, feeling, thinking, making, celebrating};
        Post();
        Post(std::string owner, sf::Text title, sf::Text content, Activity activity, std::vector<std::string> likedBy, std::vector<Comment> comments, std::time_t date = 0 , std::string activityvalue = "");
        void AddLike(std::string id);
        void RemoveLike(std::string id);
        // void AddSprite(sf::Sprite sprite);
        // void RemoveSprite(int index);
        void draw(sf::RenderWindow& window);
        void Offset(float x, float y);
        // Delete should be called in the app class
    private:
        Activity activity;
};