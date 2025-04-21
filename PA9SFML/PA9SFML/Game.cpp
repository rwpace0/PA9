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
}

Game::~Game() {
	// function to clean up everything
}


void Game::run()
{
    Clock clock;

    while (window.isOpen())
    {
        Time dt = clock.restart();

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
}


void Game::render() {
    window.clear();

    // Draw platforms
    for (auto& platform : platforms) {
        platform.draw(window);
    }

    // Draw the player
    renderPlayer();

    window.display();
}
