#pragma once
#include "Game.hpp"

Game::Game()
{
	//call init function
}
Game::~Game() {
	// function to clean up everything
}

//window init and event handling is in here for now but separate functions will be created to handle these
void Game::run()
{
    RenderWindow window(VideoMode({ windowWidth, windowHeight }), "Game Name");

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }
}
