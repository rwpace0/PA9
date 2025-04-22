#pragma once
#ifndef GAME_HPP
#define GAME_HPP
#include "Header.hpp"
#include "Player.hpp"
#include "Platform.hpp"
#include "MovePlatform.hpp"

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
	void renderPlatforms();
	void updatePlatformMoving(Time dt);

	void update(Time dt);
	void render();

	//variables
	RenderWindow window;
	Player player;
	std::vector<Platform> platforms;
	std::vector<PlatformMoving> movePlatform;

};

#endif