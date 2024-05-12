#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button {
    protected:
        sf::RectangleShape shape;
        sf::Text displayText;
        bool active;
    public:
        Button();
        Button(float x, float y, float width, float height, sf::Text Text, int charsize = 24);
        virtual void draw(sf::RenderWindow& window);
        bool isActive(int Active = -1);
        virtual void checkClick(const sf::Vector2f& mousePosition);
        void Offset(float x, float y);
};

class TextInputField : public Button {
    private:
        std::string input;
        sf::Text inputDisplay;
        sf::Clock cursorClock;
        bool showCursor;
        float xpos, ypos, heightpar;
        sf::RectangleShape cursorLine;
    public:
        TextInputField(float x, float y, float width, float height, sf::Text Text, int charsize = 24);
        void draw(sf::RenderWindow& window) override;
        void checkClick(const sf::Vector2f& mousePosition) override;
        void handleInput(sf::Event::TextEvent event);
        void handleBackspace();
        void updateCursor();
        std::string getInput();
};