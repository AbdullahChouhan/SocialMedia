#pragma once

#include <string>

class Comment {
    private:
        std::string username;
        std::string content;
    public:
        Comment(std::string username, std::string content);
        std::string GetUsername();
        std::string GetContent();
};