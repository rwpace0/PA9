#pragma once
#include "Game.hpp"

Game::Game() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    window.create(desktopMode, "Game Name", Style::None);
    window.setFramerateLimit(frameLimit);

    // Create a floor at the bottom of the screen
    //platforms.emplace_back(
    //    sf::Vector2f(0, 850),  // Position (x, y)
    //    sf::Vector2f(800, 50)  // Size (width, height)
    //);
    //platforms.emplace_back(
    //    sf::Vector2f(700, 750),  // Position (x, y)
    //    sf::Vector2f(400, 50)  // Size (width, height)
    //);
    //platforms.emplace_back(
    //    sf::Vector2f(100, 750),  // Position (x, y)
    //    sf::Vector2f(200, 50)  // Size (width, height)
    //);

    float screenwidth = window.getSize().x;
    float screenHeight = window.getSize().y;


    float platformWidth = 150.f;
    float platformheight = 30.f;

    float bottom = screenHeight - 100.f;
    float middle = screenHeight * 0.6f;
    float top = screenHeight * 0.3f;


    float spacing = screenwidth / 3.f;
    /*bottom 2 platforms*/
    platforms.emplace_back(
        Vector2f(spacing-platformWidth/2,bottom),
        Vector2f(platformWidth,platformheight)

    );
    platforms.emplace_back(
        Vector2f(spacing * 2 - platformWidth / 2, bottom),
        Vector2f(platformWidth, platformheight)
        
    
    );

    /*middle three platforms*/

    spacing = screenwidth / 4.f;
    platforms.emplace_back(
        Vector2f(spacing - platformWidth / 2, middle),
        Vector2f(platformWidth, platformheight)
    
    );

    platforms.emplace_back(
        Vector2f(spacing * 2 - platformWidth / 2, middle),
        Vector2f(platformWidth, platformheight)

    );

    platforms.emplace_back(
        Vector2f(spacing * 3 - platformWidth / 2, middle),
        Vector2f(platformWidth, platformheight)

    );

    spacing = screenwidth / 3.f;

    platforms.emplace_back(
        Vector2f(spacing - platformWidth / 2, middle),
        Vector2f(platformWidth, platformheight)

    );

    platforms.emplace_back(
        Vector2f(spacing * 2 - platformWidth / 2, middle),
        Vector2f(platformWidth, platformheight)

    );





}


void Game::renderPlatforms()
{
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
