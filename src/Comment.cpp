#include "headers/Comment.hpp"

Comment::Comment(std::string username, std::string content) {
    this->username = username;
    this->content = content;
}

std::string Comment::GetUsername() {
    return username;
}

std::string Comment::GetContent() {
    return content;
}