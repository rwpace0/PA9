#pragma once
#include "Game.hpp"

Game::Game()
{
    init();
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

// init all vars
void Game::init() {
    this->window = nullptr;
    
}

void Game::handleInput() {

}

void Game::update()
{
    //call all update functions
}

void Game::render()
{
    //call all render functions
}