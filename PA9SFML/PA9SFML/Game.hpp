#pragma once
#ifndef GAME_HPP
#define GAME_HPP
#include "Header.hpp"

class Game {
public:
	//constructor destructor
	Game();
	~Game();

	//for now running the window and init is in this function
	void run();

private:
	
	//functions

	//init
	//will have to use when there are more functions but for now everything is in run()
	void initVars();
	void initWindow();
	void initResources();
	void initEntities();

	// 
	void handleInput();
	//will need sub functions like updatePlayer, renderPlatform, etc.
	void update();
	void render();

	//variables
	RenderWindow* window;

	// other variables for input, textures, ui, etc will go here


};

#endif