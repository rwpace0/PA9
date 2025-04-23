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

    // Debug visualization
    sf::RectangleShape getDebugShape() const {
        sf::RectangleShape debugShape(size);
        debugShape.setPosition(position);
        debugShape.setFillColor(sf::Color(255, 0, 0, 120)); // Semi-transparent red

        // Color-code collision types
        if (collidedWithProjectile) {
            debugShape.setOutlineColor(sf::Color::Magenta);
        }
        else if (collidedWithMovingPlatform) {
            debugShape.setOutlineColor(sf::Color::Cyan);
        }
        else {
            debugShape.setOutlineColor(sf::Color::White);
        }

        debugShape.setOutlineThickness(1.5f);
        return debugShape;
    }
};

namespace Physics {
    bool AABB(const sf::FloatRect& a, const sf::FloatRect& b);
    void resolveCollision(
        PhysicsComponent& dynamic,
        const sf::FloatRect& staticObj,
        const sf::Vector2f& platformVelocity = sf::Vector2f(0, 0)
    );

    // Optional: Global debug draw helper
    void drawDebug(sf::RenderTarget& target, const PhysicsComponent& phys);
}