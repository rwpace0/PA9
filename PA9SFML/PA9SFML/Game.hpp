#pragma once
#ifndef GAME_HPP
#define GAME_HPP
#include "Header.hpp"

class Game {
public:
	//constructor destructor
	Game();
	~Game();

	//for now running the window
	//the run function will just call update and render in the future
	void run();

private:
	
	//functions

	//init all vars
	void init();

	// 
	void handleInput();
	//will need sub functions like updatePlayer, renderPlatform, etc
	void update();
	void render();

	//variables
	RenderWindow* window;

	// other variables for input, textures, ui, etc will go here


};

#endif