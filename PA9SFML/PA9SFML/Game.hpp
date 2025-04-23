#pragma once
#ifndef GAME_HPP
#define GAME_HPP
#include "Header.hpp"
#include "Player.hpp"
#include "Platform.hpp"
#include "Menu.hpp"
#include "Enemy.hpp"
#include <random>

#include "MovePlatform.hpp"

enum class GameState {
	MENU,
	PLAYING,
	PAUSED,
	GAME_OVER
};

class Game {
public:
	//constructor destructor
	Game();
	~Game();

	//for now running the window
	void run();

	enum class GameState {
		MENU,
		PLAYING,
		PAUSED,
		GAME_OVER,
	};

private:
	GameState currentState = GameState::MENU;
	Menu* menu = nullptr;

	void processEvents();
	void handleMenuState(sf::Time dt);
	void handlePlayingState(sf::Time dt);
	void handlePausedState(sf::Time dt);


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
	
	//time
	Clock gameClock;
	Clock deltaClock;
	
	//text
	Font font;
	Text *timeText = nullptr;

	//time
	void initTime();
	void updateTime();

	std::vector<Enemy> enemies;


	//ENEMY Spawning Variables
	float spawnRateSec = 10.f;
	float timeSinceLastSpawn = 0.f;
	sf::Time enemySpawnInterval = sf::seconds(spawnRateSec);


	std::vector<PlatformMoving> movePlatform;


};

#endif