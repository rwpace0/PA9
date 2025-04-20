#pragma once
#include <SFML/Graphics.hpp>
#include "physics.hpp"

class Platform {
public:
    Platform(const sf::Vector2f& position, const sf::Vector2f& size);

    const sf::FloatRect& getBounds() const;
    void draw(sf::RenderTarget& target);

private:
    sf::RectangleShape shape;
    PhysicsComponent physics; // For collision (no gravity/movement)
};