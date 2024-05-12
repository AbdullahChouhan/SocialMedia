#pragma once

#include <string>
#include <vector>

#include "Post.hpp"

class User {
    private:
        friend class Feed;
        std::string name;
        std::vector<User*> friends;
        std::vector<Post> posts;
    public:
        User(const std::string& username);
        void AddFriend(const std::string& friendName);
        void RemoveFriend(const std::string& friendName);
        void AddPost(const Post& post);
        void RemovePost(int index);
};

class Page {
    private:
        std::string name, ownername;
        std::vector<Post> posts;
    public:
        Page(const std::string& username);
        void AddPost(const Post& post);
        void RemovePost(int index);
};