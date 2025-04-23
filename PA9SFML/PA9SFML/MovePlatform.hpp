#pragma once
#include "Platform.hpp"
/*enum class was used to avoid implicit conversions*/
enum class Movement {
	/*in a enum class the data members are always public*/
	horizontal,
	Vertical
};


class PlatformMoving : public Platform {

public:
	PlatformMoving(const sf::Vector2f& position, const sf::Vector2f& size, Movement type, float speed, float distance);

	void update(float dt);
private:

	Movement movement;
	float speed;
	float distance;
	float traveled = 0.6f;
	sf::Vector2f start;
	int direction = 1;






};