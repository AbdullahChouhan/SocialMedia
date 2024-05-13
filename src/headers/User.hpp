#pragma once

#include <string>
#include <vector>

#include "Post.hpp"

class User {
    private:
        friend class Feed;
        std::string name;
        std::vector<std::string> friends;
        std::vector<Post> posts;
    public:
        User(const std::string& username);
        void AddFriend(const std::string& friendName);
        void RemoveFriend(const std::string& friendName);
        void AddPost(Post post);
        void RemovePost(int index);
};

class Page {
    private:
        std::string name, ownername;
        std::vector<Post> posts;
    public:
        Page(const std::string& username, const std::string& ownername);
};