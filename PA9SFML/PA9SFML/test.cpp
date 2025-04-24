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
