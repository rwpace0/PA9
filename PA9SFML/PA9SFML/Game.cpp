#pragma once
#include "Game.hpp"

Game::Game()
{
    window.create(VideoMode({ windowWidth, windowHeight }), "Game Name");
    window.setFramerateLimit(frameLimit);
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

void Game::update(Time dt)
{
    
    while (const optional event = window.pollEvent()) {

        if (event->is<Event::Closed>()) {
            window.close();
        }

    }

    player.update(dt);
}

void Game::render()
{
    window.clear();

    renderPlayer();

    window.display();
}