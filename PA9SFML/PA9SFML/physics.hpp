#pragma once
#include <SFML/Graphics.hpp>

struct PhysicsComponent {

  
    sf::Vector2f position;  // Top-left corner
    sf::Vector2f size;      // Width/height
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    bool isGrounded = false;
    bool receivesGravity = true;
    bool isPlayer = false;

    // Collision tracking
    bool collidedWithProjectile = false;
    bool collidedWithMovingPlatform = false;
    sf::Vector2f platformVelocity;

    sf::FloatRect getBounds() const {
        return sf::FloatRect(position, size);
    }

    void update(float deltaTime, const sf::Vector2f& gravity) {
		isGrounded = false; // Reset grounded state
        if (receivesGravity) {
            acceleration += gravity;
        }

        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
        acceleration = { 0, 0 }; // Reset acceleration
    }
};

namespace Physics {
    bool AABB(const sf::FloatRect& a, const sf::FloatRect& b);
    void resolveCollision(
        PhysicsComponent& dynamic,
        const sf::FloatRect& staticObj,
        const sf::Vector2f& platformVelocity = sf::Vector2f(0, 0)
    );
}