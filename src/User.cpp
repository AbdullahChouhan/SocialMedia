#include "headers/User.hpp"

User::User(const std::string& username) {
    this->name = username;
}

void User::AddFriend(const std::string& friendName) {
    this->friends.push_back(friendName);
}

void User::RemoveFriend(const std::string& friendName) {
    this->friends.erase(std::remove(this->friends.begin(), this->friends.end(), friendName), this->friends.end());
}

void User::AddPost(Post post) {
    this->posts.push_back(post);
}

void User::RemovePost(int index) {
    this->posts.erase(this->posts.begin() + index);
}

Page::Page(const std::string& username, const std::string& ownername) {
    this->name = username;
    this->ownername = ownername;
}