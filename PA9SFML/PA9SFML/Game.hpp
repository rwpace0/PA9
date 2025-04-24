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
	void setSpawnRate(float rate) { currentSpawnRate = rate; }
	void setEnemiesPerSpawn(int count) { currentEnemiesPerSpawn = count; }

	enum class GameState {
		MENU,
		PLAYING,
		PAUSED,
		GAME_OVER,
	};

private:
	GameState currentState = GameState::MENU;
	Menu* menu = nullptr;
	float lastInputTime = 0.0f;
	const float inputCooldown = 0.2f;
	bool isPaused = false;

	void processEvents(sf::Time dt);
	void handleMenuState(sf::Time dt);
	void handlePlayingState(sf::Time dt);
	void handlePausedState(sf::Time dt);
	void handleGameOverState(Time dt);


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
	float timeSinceLastSpawn = 0.0f; // Tracks time since the last enemy spawn
	float baseSpawnRate = 2.0f; // The original spawn rate in seconds
	float currentSpawnRate = baseSpawnRate; // The current spawn rate
	int baseEnemiesPerSpawn = 1; // The original number of enemies per spawn
	int currentEnemiesPerSpawn = baseEnemiesPerSpawn; // The current number of enemies per spawn
	float difficultyTimer = 0.0f;
	sf::Time enemySpawnInterval = sf::seconds(currentSpawnRate);


	std::vector<PlatformMoving> movePlatform;

	bool gameOverDrawn = false;

};

#endif