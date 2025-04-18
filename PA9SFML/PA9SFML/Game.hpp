#pragma once
#ifndef GAME_HPP
#define GAME_HPP
#include "Header.hpp"
#include "Player.hpp"

class Game {
public:
	//constructor destructor
	Game();
	~Game();

	//for now running the window
	void run();

private:
	
	//functions
	void updatePlayer();
	void renderPlayer();

	void update(Time dt);
	void render();

	//variables
	RenderWindow window;
	Player player;

};

#endif