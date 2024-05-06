#include "headers/Post.hpp"
#include "headers/ResourceManager.hpp"

Post::Post() {}

Post::Post(std::string* id, std::string title, std::string content) {
    this->ownderId = id;
    this->title = title;
    this->content = content;
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime = *std::localtime(&currentTime);
    this->date = localTime;
    this->likes = 0;
    ResourceManager rm = ResourceManager::GetInstance();
    rm.AddPost(*id, *this);
}

void Post::AddLike(std::string* id) {
    this->likes ++;
    if (std::find(this->likedBy.begin(), this->likedBy.end(), id) == this->likedBy.end())
        this->likedBy.push_back(id);
}

void Post::RemoveLike(std::string* id) {
    this->likes --;
    this->likedBy.erase(std::remove(this->likedBy.begin(), this->likedBy.end(), id), this->likedBy.end());
}

void Post::AddTexture(sf::Texture texture) {
    this->textures.push_back(texture);    
}

void Post::RemoveTexture(int index) {
    this->textures.erase(this->textures.begin() + index);
}