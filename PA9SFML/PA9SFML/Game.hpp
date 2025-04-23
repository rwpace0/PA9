#pragma once
#ifndef GAME_HPP
#define GAME_HPP
#include "Header.hpp"
#include "Player.hpp"
#include "Platform.hpp"

#include "Enemy.hpp"
#include <random>

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

	std::vector<Enemy> enemies;


	//ENEMY Spawning Variables
	float spawnRateSec = 10.f;
	float timeSinceLastSpawn = 0.f;
	sf::Time enemySpawnInterval = sf::seconds(spawnRateSec);


	std::vector<PlatformMoving> movePlatform;


};

#endif