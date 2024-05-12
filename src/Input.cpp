#include "headers/Input.hpp"

Button::Button() {}

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

void Button::Offset(float x, float y) {
    shape.setPosition(shape.getPosition().x + x, shape.getPosition().y + y);
}

TextInputField::TextInputField(float x, float y, float width, float height, sf::Text Text, int charsize) : Button(x, y, width, height, Text, charsize), showCursor(false) {
    input.clear();
    input = "";

    xpos = x;
    ypos = y;
    heightpar = height;

    displayText.setFillColor(sf::Color(100, 100, 102));

    inputDisplay = displayText;
    inputDisplay.setFillColor(sf::Color::White);
    inputDisplay.setString(input);
    inputDisplay.setPosition(x + 5.f, y + (height - displayText.getGlobalBounds().height) / 2);
    displayText.setPosition(x + 5.f, y + (height - displayText.getGlobalBounds().height) / 2);

    cursorLine.setFillColor(sf::Color::White);
    cursorLine.setSize(sf::Vector2f(2.f, displayText.getGlobalBounds().height));
    cursorLine.setPosition(x + 7.f, y + (height - inputDisplay.getGlobalBounds().height) / 2);
    heightpar = y + (height - inputDisplay.getGlobalBounds().height) / 2;
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
            float real = ypos + (heightpar - inputDisplay.getGlobalBounds().height) / 2;
            cursorLine.setPosition(sf::Vector2f(xpos + 7.f + inputDisplay.getGlobalBounds().width, heightpar));
        }
        else if (event.unicode < 128) {
            input += event.unicode;
            inputDisplay.setString(input);
            cursorClock.restart();
            float real = ypos + (heightpar - inputDisplay.getGlobalBounds().height) / 2;
            cursorLine.setPosition(sf::Vector2f(xpos + 7.f + inputDisplay.getGlobalBounds().width, heightpar));
        }
    }
}

void TextInputField::handleBackspace() {
    if (!input.empty()) {
        input = input.substr(0, input.length() - 1);
        inputDisplay.setString(input);
        cursorClock.restart();
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

std::string TextInputField::getInput() {
    return input;
}