#include "headers/Input.hpp"

Button::Button(float x, float y, float width, float height, sf::Text Text, int charsize) : shape(sf::Vector2f(width, height)), displayText(Text), active(false) {
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(28, 28, 30));
    
    displayText.setCharacterSize(charsize);
    displayText.setFillColor(sf::Color::White);
    displayText.setPosition(x + (width - displayText.getGlobalBounds().width) / 2, y + (height - displayText.getGlobalBounds().height) / 2);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(displayText);
}

bool Button::isActive(int Active) {
    if (Active == 1) {
        active = true;
    }
    else if (Active == 0) {
        active = false;
    }
    return active;
}

void Button::checkClick(const sf::Vector2f& mousePosition) {
    if (shape.getGlobalBounds().contains(mousePosition)) {
        active = true;
    }
    else {
        active = false;
    }
}

TextInputField::TextInputField(float x, float y, float width, float height, sf::Text Text, int charsize) : Button(x, y, width, height, Text, charsize), showCursor(false) {
    input.clear();
    input = "";

    displayText.setFillColor(sf::Color(44, 44, 46));

    inputDisplay.setCharacterSize(charsize);
    inputDisplay.setFillColor(sf::Color::White);
    inputDisplay.setString(input);
    inputDisplay.setPosition(x + 5.f, y + (height - inputDisplay.getGlobalBounds().height) / 2);

    cursorLine.setFillColor(sf::Color::White);
    cursorLine.setSize(sf::Vector2f(2.f, inputDisplay.getGlobalBounds().height));
    cursorLine.setPosition(x + 5.f, y + (height - inputDisplay.getGlobalBounds().height) / 2);
}

void TextInputField::draw(sf::RenderWindow& window) {
    window.draw(shape);
    if (input == "")
        window.draw(displayText);
    else
        window.draw(inputDisplay);
    if (showCursor)
        window.draw(cursorLine);
}

void TextInputField::checkClick(const sf::Vector2f& mousePosition) {
    if (shape.getGlobalBounds().contains(mousePosition)) {
        active = true;
        cursorClock.restart();
    }
    else {
        active = false;
    }
}

void TextInputField::handleInput(sf::Event::TextEvent event) {
    if (active) {
        if (event.unicode == 8) {
            handleBackspace();
        }
        else if (event.unicode < 128) {
            input += event.unicode;
            inputDisplay.setString(input);
        }
    }
}

void TextInputField::handleBackspace() {
    if (!input.isEmpty()) {
        input = input.substring(0, input.getSize() - 1);
        inputDisplay.setString(input);
    }
}

void TextInputField::updateCursor() {
    if (active) {
        if (cursorClock.getElapsedTime().asSeconds() >= 0.5f) {
            showCursor = !showCursor;
            cursorClock.restart();
        }
    }
    else {
        showCursor = false;
    }
}