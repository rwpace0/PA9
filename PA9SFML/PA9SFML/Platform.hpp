#pragma once
#include <SFML/Graphics.hpp>
#include "physics.hpp"

class Platform {
public:
    Platform(const sf::Vector2f& position, const sf::Vector2f& size);
    virtual ~Platform() = default;

    const sf::FloatRect& getBounds() const;
    virtual void draw(sf::RenderTarget& target);

protected:
    sf::RectangleShape shape;
    PhysicsComponent physics; // For collision (no gravity/movement)
};