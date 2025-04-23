#include "Menu.hpp"

Menu::Menu(RenderWindow& window) : window(window) {

    if (!font.openFromFile("Fonts/pixelfont.otf")) {
        throw std::runtime_error("Failed to load Pixel Font, Menu.cpp");
    }
    titleText = new sf::Text(font, "Game Name", 100);
    titleText->setFillColor(sf::Color::White);

    // CENTER
    sf::Vector2f newOrigin{
        (bounds.position.x + bounds.size.x) * 0.5f,
        bounds.position.y
    };
    titleText->setOrigin(newOrigin);

    sf::Vector2f pos{
        static_cast<float>(window.getSize().x) * 0.5f,
        window.getSize().y * 0.2f
    };
    titleText->setPosition(pos);

   // spacing and start pos
    float verticalSpacing = 80.0f;
    float startY = window.getSize().y * 0.4f;

    menuItems.emplace_back(font, "Start", sf::Vector2f(window.getSize().x / 2.0f, startY));
    menuItems.emplace_back(font, "Options", sf::Vector2f(window.getSize().x / 2.0f, startY + verticalSpacing));
    menuItems.emplace_back(font, "Exit", sf::Vector2f(window.getSize().x / 2.0f, startY + verticalSpacing * 2));

    //set first item as selected
    menuItems[selectedItemIndex].setSelected(true);
}

Menu::~Menu() {
    delete titleText;
}

void Menu::handleInput() {
    
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
            menuItems[selectedItemIndex].setSelected(false);
            selectedItemIndex = (selectedItemIndex - 1 + static_cast<int>(menuItems.size())) % static_cast<int>(menuItems.size());
            menuItems[selectedItemIndex].setSelected(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
            menuItems[selectedItemIndex].setSelected(false);
            selectedItemIndex = (selectedItemIndex + 1) % static_cast<int>(menuItems.size());
            menuItems[selectedItemIndex].setSelected(true);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter)) {
            itemSelected = true;
    }
    
}

void Menu::update(float dt) {
    // probably dont need
}

void Menu::draw() {
    // Draw title
    window.draw(*titleText);

    // Draw menu items
    for (auto& item : menuItems) {
        item.draw(window);
    }
}