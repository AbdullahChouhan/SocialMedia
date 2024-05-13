#include "headers/Post.hpp"
#include "headers/ResourceManager.hpp"

Post::Post() {}

Post::Post(std::string owner, sf::Text title, sf::Text content, Activity activity, std::vector<std::string> likedBy, std::vector<Comment> comments, std::time_t date, std::string activityvalue) : likedBy(likedBy), comments(comments) {
    this->ownername = owner;
    this->title = title;
    this->content = content;
    this->activity = activity;
    this->activityvalue = activityvalue;
    this->date = date;
    this->likeButton = Button(title.getPosition().x + title.getGlobalBounds().width, title.getPosition().y, 50, 50, rm.CreateText("Like"));
    this->viewComments = Button(title.getPosition().x + title.getGlobalBounds().width + 50, title.getPosition().y, 50, 50, rm.CreateText("Comments"));
    content.setPosition(title.getPosition().x, title.getPosition().y + title.getGlobalBounds().height);
    std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    this->date = currentTime;
    likes = likedBy.size();
}

void Post::AddLike(std::string id) {
    this->likes ++;
    if (std::find(this->likedBy.begin(), this->likedBy.end(), id) == this->likedBy.end())
        this->likedBy.push_back(id);
}

void Post::RemoveLike(std::string id) {
    this->likes --;
    this->likedBy.erase(std::remove(this->likedBy.begin(), this->likedBy.end(), id), this->likedBy.end());
}

// void Post::AddSprite(sf::Sprite sprite) {
//     this->sprites.push_back(sprite);    
// }

// void Post::RemoveSprite(int index) {
//     this->sprites.erase(this->sprites.begin() + index);
// }

void Post::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(content);
    likeButton.draw(window);
    viewComments.draw(window);
}

void Post::Offset(float x, float y) {
    title.setPosition(title.getPosition().x + x, title.getPosition().y + y);
    content.setPosition(content.getPosition().x + x, content.getPosition().y + y);
    likeButton.Offset(x, y);
}