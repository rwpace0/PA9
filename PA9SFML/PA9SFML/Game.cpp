#pragma once
#include "Game.hpp"


Game::Game() {

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    window.create(desktopMode, "Game Name", Style::None);
    window.setFramerateLimit(frameLimit);

    initTime();
    renderPlatforms();

    menu = new Menu(window);
    // Create a floor at the bottom of the screen
   

}


void Game::renderPlatforms()
{

    float screenwidth = window.getSize().x;
    float screenHeight = window.getSize().y;


    float platformWidth = screenwidth * 0.125f;
    float platformheight = screenHeight * 0.01f;

    float r1 = screenHeight * 0.85f;
    float r2 = screenHeight * 0.72f;
    float r3 = screenHeight * 0.60f;
    float r4 = screenHeight * 0.45f;


    float speed = screenwidth * 0.075f;
    float distance_direction = screenwidth * 0.15f;

    float spacing = screenwidth / 4.f;
    /*bottom platforms that moves side to side*/
   
    movePlatform.emplace_back(
        Vector2f(screenwidth /2- platformWidth / 2, r1),
        Vector2f(platformWidth/1.5f, platformheight),Movement::horizontal,
       speed,distance_direction

    );
    /*second row with two platforms that dont move*/
    platforms.emplace_back(
        Vector2f(spacing - platformWidth / 2, r2),
        Vector2f(platformWidth/1.5f, platformheight)


    );

    platforms.emplace_back(
        Vector2f(spacing * 3 - platformWidth / 2, r2),
        Vector2f(platformWidth/1.5f, platformheight)


    );

    /*row 3 with 2 non moving platforms and one moving plaform in the middle*/

  
    platforms.emplace_back(
        Vector2f(spacing * 0.6f - platformWidth / 2, r3),
        Vector2f(platformWidth/1.5f, platformheight)

    );

    float vertical_speed = screenHeight * 0.05f;
    float vertical_distance = screenHeight * 0.075f;

    movePlatform.emplace_back(
        Vector2f(spacing * 2 - platformWidth / 2, r3),
        Vector2f(platformWidth/1.5f, platformheight),Movement::Vertical,
        vertical_speed,vertical_distance

    );

    platforms.emplace_back(
        Vector2f(spacing * 3.4f - platformWidth / 2, r3),
        Vector2f(platformWidth/1.5f, platformheight)

    );
    /*top platforms that dont move*/

    spacing = screenwidth / 4.f;

    platforms.emplace_back(
        Vector2f(spacing - platformWidth/2, r4),
        Vector2f(platformWidth/1.5f, platformheight)
    
    );

    platforms.emplace_back(
        Vector2(spacing * 3 - platformWidth/2, r4),
        Vector2f(platformWidth/1.5f,platformheight)
    );

   enemies.push_back(Enemy());
}

void Game::updatePlatformMoving(Time dt)
{
    for (auto& platform : movePlatform) {
        platform.update(dt.asSeconds());
    }


}

Game::~Game() {

    delete timeText;
	
}

void Game::run() {
    deltaClock.restart();
    gameClock.restart();

    while (window.isOpen()) {
        Time dt = deltaClock.restart(); // Calculate dt once per frame

        processEvents(dt); // Pass dt to processEvents
        switch (currentState) {
        case GameState::MENU:
            handleMenuState(dt);
            break;
        case GameState::PLAYING:
            handlePlayingState(dt);
            break;
        case GameState::PAUSED:
            handlePausedState(dt);
            break;
        case GameState::GAME_OVER:
            // Handle game over state
            break;
        }
    }
}


void Game::processEvents(Time dt) {
    lastInputTime += dt.asSeconds(); // Update the cooldown timer

    if (currentState == GameState::MENU && menu) {
        menu->handleInput(dt.asSeconds());
    }

    // Handle pause/unpause with cooldown
    if (lastInputTime >= inputCooldown && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
        if (currentState == GameState::PLAYING) {
            currentState = GameState::PAUSED;
            isPaused = false; // Reset the flag when entering the pause state
        }
        else if (currentState == GameState::PAUSED) {
            currentState = GameState::PLAYING;
        }
        lastInputTime = 0.0f; // Reset the cooldown timer
    }
}



void Game::handleMenuState(sf::Time dt) {
    window.clear(sf::Color(30, 30, 30)); // Dark background for menu

    if (menu) {
        menu->update(dt.asSeconds());
        menu->draw();

        // Check if a menu item was selected
        if (menu->isItemSelected()) {
            int selectedItem = menu->getSelectedItemIndex();
            menu->resetItemSelected();

            switch (selectedItem) {
            case 0: //Play
                currentState = GameState::PLAYING;
                // reset game state if neccessary
                gameClock.restart();
                break;
            case 1: //Options
                //need option menu
                break;
            case 2: // Exit
                window.close();
                break;
            }
        }
    }

    window.display();
}

void Game::handlePlayingState(sf::Time dt) {
    //update and render the game
    update(dt);
    render();
}

void Game::handlePausedState(sf::Time dt) {
    if (!isPaused) {
        // Draw the game first (but don't update it)
        render();

        // Draw pause overlay
        sf::RectangleShape overlay;
        overlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
        window.draw(overlay);

        // Draw pause text
        sf::Text pauseText(font, "PAUSED", 100);
        pauseText.setFillColor(sf::Color::White);

        // CENTER
        sf::FloatRect bounds = pauseText.getLocalBounds();
        sf::Vector2f newOrigin{
            (bounds.position.x + bounds.size.x) * 0.5f,
            (bounds.position.y + bounds.size.y) * 0.5f
        };
        pauseText.setOrigin(newOrigin);

        sf::Vector2f pos{
            static_cast<float>(window.getSize().x) * 0.5f,
            static_cast<float>(window.getSize().y) * 0.5f
        };
        pauseText.setPosition(pos);

        window.draw(pauseText);
        window.display();

        isPaused = true; // Mark the pause menu as rendered
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

    updatePlatformMoving(dt);

    // Handle collisions between the player and static platforms
    for (auto& platform : platforms) {
        if (Physics::AABB(player.physics.getBounds(), platform.getBounds())) {
            Physics::resolveCollision(player.physics, platform.getBounds(), sf::Vector2f(0.f, 0.f));
        }
    }

    // Handle collisions between the player and moving platforms
    for (auto& platform : movePlatform) {
        if (Physics::AABB(player.physics.getBounds(), platform.getBounds())) {
            Physics::resolveCollision(player.physics, platform.getBounds(), platform.getVelocity());
        }
    }

    // Handle collisions between the player and enemies
    for (auto& enemy : enemies) {
        if (Physics::AABB(player.physics.getBounds(), enemy.getBounds())) {
            player.reduceHealth(20); // Reduce health by 20
        }
    }

    updateTime();


    // Enemy spawning logic
    timeSinceLastSpawn += dt.asSeconds();
    difficultyTimer += dt.asSeconds(); // Update the difficulty timer

    // Gradually decrease the spawn rate over the course of a minute
    if (difficultyTimer < 60.0f) {
        currentSpawnRate = baseSpawnRate - (difficultyTimer / 60.0f) * (baseSpawnRate - 1.0f); // Slowly increase spawn rate
    }
    else {
        // After a minute, reset the difficulty timer and increase the number of enemies per spawn
        difficultyTimer = 0.0f;
        currentEnemiesPerSpawn += 1; // Add one more enemy per spawn
        currentSpawnRate = baseSpawnRate; // Reset spawn rate to base value
    }

    if (timeSinceLastSpawn >= currentSpawnRate) {
        std::random_device rand; // Seed
        std::mt19937 gen(rand()); // Random number generator
        std::uniform_real_distribution<float> distance(0.f, static_cast<float>(window.getSize().y - 50.f)); // Adjust height range

        for (int i = 0; i < currentEnemiesPerSpawn; ++i) {
            Enemy enemy;

            float y = distance(gen); // Generate a random y position
            enemy.setPosition(-enemy.getSize().x, y); // Spawn off-screen to the left
            enemies.push_back(enemy);
        }

        timeSinceLastSpawn = 0.0f; // Reset the spawn timer
    }




    // Update enemies and remove those that move off-screen
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        it->update(dt);

        // Check if the enemy is off-screen
        if (it->getBounds().position.x > window.getSize().x) {
            it = enemies.erase(it); // Remove the enemy and update the iterator
        }
        else {
            ++it; // Move to the next enemy
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


    window.draw(*timeText);

    //Render Enemy
    for (auto& enemy : enemies)
    {
        enemy.draw(window);
    }


    window.display();
}
