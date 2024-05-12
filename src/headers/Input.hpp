#pragma once

#include <SFML/Graphics.hpp>

class Button {
    protected:
        sf::RectangleShape shape;
        sf::Text displayText;
        bool active;
    public:
        Button(float x, float y, float width, float height, sf::Text Text, int charsize = 24);
        virtual void draw(sf::RenderWindow& window);
        bool isActive(int Active = -1);
        virtual void checkClick(const sf::Vector2f& mousePosition);
};

class TextInputField : public Button {
    private:
        sf::String input;
        sf::Text inputDisplay;
        sf::Clock cursorClock;
        bool showCursor;
        sf::RectangleShape cursorLine;
    public:
        TextInputField(float x, float y, float width, float height, sf::Text Text, int charsize = 24);
        void draw(sf::RenderWindow& window) override;
        void checkClick(const sf::Vector2f& mousePosition) override;
        void handleInput(sf::Event::TextEvent event);
        void handleBackspace();
        void updateCursor();
};