#include "MovePlatform.hpp"


PlatformMoving::PlatformMoving(const sf::Vector2f& position, const sf::Vector2f& size, Movement type, float speed, float distance):
	Platform(position, size),movement(type), speed(speed),distance(distance),start(position)
{
}

void PlatformMoving::update(float dt) {

	float movement = speed * dt * direction;

	traveled += std::abs(movement);


	if (traveled >= distance) {
		direction *= -1;
		traveled = 0.0f;
	}
	sf::Vector2f newPosition = physics.position;

	if (this->movement == Movement::horizontal) {
		newPosition.x += movement;
	}
	else {

		newPosition.y += movement;
	}

	physics.position = newPosition;
	shape.setPosition(newPosition);


}