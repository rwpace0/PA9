#include "test.hpp"
#include <iostream>

bool test::test_creation() {

	std::cout << "testing enemy creation" << std::endl;

	try {

		Enemy enemy;

		std::cout << "Success" << std::endl;
		return true;
	}
	catch (...) {
		std::cout << "failed" << std::endl;
		return false;
	}

	
}

bool test::test_player_position(){

	Player player;

	std::cout << "testing player position" << std::endl;

	sf::Vector2f startPos = player.physics.position;

	if (startPos.x == 400.f && startPos.y == 30.f) 
	{
		cout << "success" << std::endl;
		return true; 
	}
	else 
	{
		std::cout << "failed" << std::endl;
		return false;
	}

}

bool test::test_player_speed()
{

	Player player;

	std::cout << "testing player speed" << std::endl;

	sf::Vector2f initialVelocity = player.physics.velocity;

	if (initialVelocity.x == 0.f && initialVelocity.y == 0.f)
	{
		std::cout << "success" << std::endl;
		return true;
	}
	else
	{
		std::cout << "failed" << std::endl;
		return false;
	}


}

bool test::test_health()
{
	Player player;

	std::cout << "testing player health" << std::endl;

	int health = player.getHealth();

	if (health == 100) 
	{
		std::cout << "success" << std::endl;
		return true; 
	}
	else
	{
		std::cout << "failed" << std::endl;
		return false;
	}

}



}

bool test::test_movement() {

	std::cout << "testing movement" << std::endl;

	Enemy enemy;

	sf::FloatRect in_position = enemy.getBounds();

	enemy.update(sf::seconds(0.1f));

	sf::FloatRect newPosition = enemy.getBounds();

	bool success = newPosition.position.x > in_position.position.x;

	std::cout << "movement test: " << (success ? "passed" : "failed") << std::endl;

	return success;


}

bool test::test_speed()
{
	std::cout << "testing speed" << std::endl;
	Enemy enemy;

	float testspeed = 500.0f;

	enemy.setSpeed(testspeed);

	sf::FloatRect init_position = enemy.getBounds();

	float test_time = 0.1f;

	enemy.update(sf::seconds(test_time));

	sf::FloatRect new_position = enemy.getBounds();

	float expected = testspeed * test_time;

	float reality = new_position.position.x - init_position.position.x;

	bool success = std::abs(reality - expected) < 0.1f;

	std::cout << "Enemy speed: " << (success ? "passed" : "failed") << std::endl;

	return success;
	
}

bool test::run_tests()
{
	bool creation = test_creation();
	bool movement = test_movement();
	bool speed = test_speed();


	bool passed = creation && movement && speed;

	std::cout << "\n summary: " << std::endl;
	std::cout << "creation test: " << (creation ? "passed" : "failed") << std::endl;
	std::cout << "movement test: " << (movement ? "passed" : "failed") << std::endl;
	std::cout << "speed test: " << (movement ? "passed" : "failed") << std::endl;

std:cout << "overall: " << (passed ? "all passed" : "some") << std::endl;

	return passed;

}



