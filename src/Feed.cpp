#include "headers/Feed.hpp"

Feed::Feed() {}

Feed::Feed(User* ActiveUser) : ActiveUser(ActiveUser) {}

Feed& Feed::GetInstance(User* ActiveUser) {
    static Feed instance(ActiveUser);
    return instance;
}

void Feed::populateFeed(std::unordered_map<std::string, User*>& users) {
    time_t currentTime = time(nullptr);
    for (auto& user : ActiveUser->friends) {
        for (auto& post : users[user]->posts) {
            double diff = difftime(currentTime, post.date);
            if (diff < 60 * 60 * 24) {
                posts.push_back(&post);
            }
        }
    }
}

void Feed::scrollFeed(sf::Event::MouseWheelScrollEvent event) {
    if (posts.size() > 0) {
        if (event.delta != 0) {
            if (event.delta > 0) {
                if (posts[0]->title.getPosition().y >= 100.f)
                    posts[0]->title.setPosition(posts[0]->title.getPosition().x, posts[0]->title.getPosition().y + event.delta * 10);
            }
            else if (event.delta < 0) {
                if (posts[0]->title.getPosition().y <= 980.f)
                    posts[0]->title.setPosition(posts[0]->title.getPosition().x, posts[0]->title.getPosition().y - event.delta * 10);
            }
        }
    }
}

void Feed::drawFeed(sf::RenderWindow& window) {
    for (auto& post : posts) {
        post->draw(window);
    }
}