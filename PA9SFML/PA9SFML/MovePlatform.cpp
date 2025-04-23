#include "MovePlatform.hpp"


PlatformMoving::PlatformMoving(const sf::Vector2f& position, const sf::Vector2f& size, Movement type, float speed, float distance):
	Platform(position, size),movement(type), speed(speed),distance(distance),start(position)
{
}

void PlatformMoving::update(float dt) {
    float movement = speed * direction; // Remove dependency on dt
    traveled += std::abs(movement) * dt; // Scale traveled distance by dt

    if (traveled >= distance) {
        direction *= -1;
        traveled = 0.0f;
    }

    sf::Vector2f newPosition = physics.position;

    if (this->movement == Movement::horizontal) {
        velocity = { movement, 0.f };
        newPosition.x += movement * dt; // Scale position update by dt
    }
    else {
        velocity = { 0.f, movement };
        newPosition.y += movement * dt; // Scale position update by dt
    }

    physics.position = newPosition;
    shape.setPosition(newPosition);
}


