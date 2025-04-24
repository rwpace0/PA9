#pragma once 
#ifndef test_hpp
#define test_hpp

#include "Enemy.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

class test {


public:

	static bool test_creation();

	static bool test_movement();

	static bool test_position();

	static bool test_speed();

	static bool test_bound();

	static bool run_tests();

	static bool test_health();

	static bool test_player_speed();

	static bool test_player_position();

};


#endif