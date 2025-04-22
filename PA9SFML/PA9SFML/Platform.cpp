#include "Platform.hpp"

Platform::Platform(const sf::Vector2f& position, const sf::Vector2f& size) {
    // Visual
    shape.setSize(size);
    shape.setPosition(position);
    shape.setOrigin(sf::Vector2f(0.f, 0.f)); // Ensure the origin is at the top-left corner
    shape.setFillColor(sf::Color::White);

    // Physics (static collider)
    physics.position = position;
    physics.size = size;
    physics.receivesGravity = false; // Critical for static objects
}


const sf::FloatRect& Platform::getBounds() const {
    return physics.getBounds(); // From PhysicsComponent
}

void Platform::draw(sf::RenderTarget& target) {
    target.draw(shape); // Draw visual platform
    Physics::drawDebug(target, physics); // Draw hitbox (red)
}