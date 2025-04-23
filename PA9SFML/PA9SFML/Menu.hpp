#pragma once
#ifndef MENU_HPP
#define MENU_HPP
#include "Header.hpp"

class MenuItem {
public:
    MenuItem(const sf::Font& font, const std::string& text, const sf::Vector2f& position) {
        this->text = new sf::Text(font, text, 50);
        this->text->setFillColor(sf::Color::White);

        // Center text
        sf::FloatRect bounds = this->text->getLocalBounds();
        sf::Vector2f newOrigin{
            (bounds.position.x + bounds.size.x) * 0.5f,
            (bounds.position.y + bounds.size.y) * 0.5f
        };
        this->text->setOrigin(newOrigin);
        this->text->setPosition(position);
    }

    ~MenuItem() {
        
    }

    void setSelected(bool selected) {
        if (selected) {
            text->setFillColor(sf::Color::Yellow);
            text->setScale(Vector2f(1.1f, 1.1f));
        }
        else {
            text->setFillColor(sf::Color::White);
            text->setScale(Vector2f(1.0f, 1.0f));
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(*text);
    }

    sf::FloatRect getBounds() const {
        return text->getGlobalBounds();
    }

private:
    sf::Text* text;
};

class Menu {
public:
    Menu(sf::RenderWindow& window);
    ~Menu();

    void handleInput(float dt);
    void update(float dt);
    void draw();

    int getSelectedItemIndex() const { return selectedItemIndex; }
    bool isItemSelected() const { return itemSelected; }
    void resetItemSelected() { itemSelected = false; }

private:
    sf::RenderWindow& window;
    std::vector<MenuItem> menuItems;
    int selectedItemIndex = 0;
    bool itemSelected = false;
    float lastInputTime = 0.0f;
    const float inputCooldown = 0.2f;

    sf::Font font;
    sf::Text* titleText;
};
#endif // !MENU_HPP