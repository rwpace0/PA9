#pragma once
#include "Game.hpp"

Game::Game() {

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    window.create(desktopMode, "Game Name", Style::None);
    window.setFramerateLimit(frameLimit);

    // Create a floor at the bottom of the screen
    platforms.emplace_back(
        sf::Vector2f(0, 850),  // Position (x, y)
        sf::Vector2f(800, 50)  // Size (width, height)
    );
    platforms.emplace_back(
        sf::Vector2f(700, 750),  // Position (x, y)
        sf::Vector2f(400, 50)  // Size (width, height)
    );
    platforms.emplace_back(
        sf::Vector2f(100, 750),  // Position (x, y)
        sf::Vector2f(200, 50)  // Size (width, height)
    );
    initTime();
}

Game::~Game() {

    delete timeText;
	
}


void Game::run()
{
    deltaClock.restart();
    gameClock.restart();

    while (window.isOpen())
    {
        Time dt = deltaClock.restart();

        update(dt);
        render();
    }
}

void Game::updatePlayer()
{
    
}

void Game::renderPlayer()
{
    player.draw(window);
}

void Game::initTime()
{
    if (!font.openFromFile("Fonts/pixelfont.otf")) {
        throw std::runtime_error("Failed to Pixel Font");
    }
    
    timeText = new Text(font,"Time", 100);
    timeText->setFillColor(Color::White);
    
    updateTime();
}

void Game::updateTime()
{
    float seconds = gameClock.getElapsedTime().asSeconds();
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << seconds; // display it to the screen as a string
    timeText->setString(ss.str());

    // CENTER TEXT
    FloatRect bounds = timeText->getLocalBounds();
    Vector2f newOrigin{
        (bounds.position.x + bounds.size.x) * 0.5f, bounds.position.y
    };
    timeText->setOrigin(newOrigin);


    sf::Vector2f pos{
        static_cast<float>(window.getSize().x) * 0.5f,
        10.f
    };
    timeText->setPosition(pos);
}

void Game::update(Time dt) {
    while (const optional event = window.pollEvent()) {
        if (event->is<Event::Closed>()) {
            window.close();
        }
    }

    player.update(dt);

    // Handle collisions between the player and platforms
    for (auto& platform : platforms) {
        if (Physics::AABB(player.physics.getBounds(), platform.getBounds())) {
            Physics::resolveCollision(player.physics, platform.getBounds());
        }
    }
    updateTime();
}


void Game::render() {
    window.clear();

    // Draw platforms
    for (auto& platform : platforms) {
        platform.draw(window);
    }

    // Draw the player
    renderPlayer();

    window.draw(*timeText);

    window.display();
}
