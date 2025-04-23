#pragma once
#include "Game.hpp"

Game::Game() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    window.create(desktopMode, "Game Name", Style::None);
    window.setFramerateLimit(frameLimit);


    renderPlatforms();


    // Create a floor at the bottom of the screen
   

}


void Game::renderPlatforms()
{

    float screenwidth = window.getSize().x;
    float screenHeight = window.getSize().y;


    float platformWidth = 250.f;
    float platformheight = 25.f;

    float r1 = screenHeight * 0.85f;
    float r2 = screenHeight * 0.7f;
    float r3 = screenHeight * 0.55f;
    float r4 = screenHeight * 0.3f;


    float spacing = screenwidth / 4.f;
    /*bottom platforms that moves side to side*/
   
    movePlatform.emplace_back(
        Vector2f(screenwidth /2- platformWidth / 2, r1),
        Vector2f(platformWidth, platformheight),Movement::horizontal,
        150.f,300.f

    );
    /*second row with two platforms that dont move*/
    platforms.emplace_back(
        Vector2f(spacing  - platformWidth / 2, r2),
        Vector2f(platformWidth, platformheight)


    );

    platforms.emplace_back(
        Vector2f(spacing * 3 - platformWidth / 2, r2),
        Vector2f(platformWidth, platformheight)


    );

    /*row 3 with 2 non moving platforms and one moving plaform in the middle*/

  
    platforms.emplace_back(
        Vector2f(spacing - platformWidth / 2, r3),
        Vector2f(platformWidth, platformheight)

    );

    movePlatform.emplace_back(
        Vector2f(spacing * 2 - platformWidth / 2, r3),
        Vector2f(platformWidth, platformheight),Movement::Vertical,
        100.f,150.f

    );

    platforms.emplace_back(
        Vector2f(spacing * 3 - platformWidth / 2, r3),
        Vector2f(platformWidth, platformheight)

    );
    /*top platforms that moves side to side*/

    spacing = screenwidth / 4.f;

    movePlatform.emplace_back(
        Vector2f(spacing * 2 - platformWidth / 2, r4),
        Vector2f(platformWidth, platformheight),
        Movement::horizontal,200.f,350.f

    );

  


}

void Game::updatePlatformMoving(Time dt)
{
    for (auto& platform : movePlatform) {
        platform.update(dt.asSeconds());
    }

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

    updatePlatformMoving(dt);

    // Handle collisions between the player and platforms
    for (auto& platform : platforms) {
        if (Physics::AABB(player.physics.getBounds(), platform.getBounds())) {
            Physics::resolveCollision(player.physics, platform.getBounds());
        }
    }

    for (auto& platform : movePlatform) {
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

    for (auto& platform : movePlatform) {
        platform.draw(window);
    }
    // Draw the player
    renderPlayer();

    window.display();
}
