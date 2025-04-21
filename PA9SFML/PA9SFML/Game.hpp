#pragma once
#ifndef GAME_HPP
#define GAME_HPP
#include "Header.hpp"
#include "Player.hpp"
#include "Platform.hpp"

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

	

	void update(Time dt);
	void render();

	//variables
	RenderWindow window;
	Player player;
	std::vector<Platform> platforms;
	
	//time
	Clock gameClock;
	Clock deltaClock;
	
	//text
	Font font;
	Text *timeText = nullptr;

	//time
	void initTime();
	void updateTime();

};

#endif