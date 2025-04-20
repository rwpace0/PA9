#pragma once
#include <SFML/Graphics.hpp>

struct PhysicsComponent {
    sf::Vector2f position;  // Top-left corner
    sf::Vector2f size;      // Width/height
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    bool isGrounded = false;
    bool receivesGravity = true;

    // Get bounds as SFML FloatRect
    sf::FloatRect getBounds() const {
        return sf::FloatRect(position, size);
    }

    void update(float deltaTime, const sf::Vector2f& gravity) {
        if (receivesGravity) acceleration += gravity;
        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
        acceleration = { 0, 0 };
    }
};

namespace Physics {
    // Collision check (unchanged)
    bool AABB(const sf::FloatRect& a, const sf::FloatRect& b);

    // SFML 3.0+ collision resolution   
    void resolveCollision(PhysicsComponent& dynamic, const sf::FloatRect& staticObj);
}
