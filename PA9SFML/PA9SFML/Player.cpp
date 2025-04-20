#include "Player.hpp"
#include <stdexcept>

Player::Player() : startPos(400.f, 30.f) {
    initTexture();
    initSprite();
    initStartPos();

    // Initialize physics (hitbox typically smaller than sprite)
    physics.size = { 30.f, 50.f };  // Width/height of collision box
    physics.position = startPos;
    physics.receivesGravity = true;
}

void Player::initSprite() {
    sprite.emplace(texture);
}

void Player::initTexture() {
    if (!texture.loadFromFile("Textures/player_walk_2.png")) {
        throw std::runtime_error("Failed to load player texture");
    }
}

void Player::initStartPos() {
    sprite->setPosition(startPos);
    physics.position = startPos;
}

void Player::update(sf::Time dt) {
    const float seconds = dt.asSeconds();

    // Reset horizontal velocity to prevent gliding
    physics.velocity.x = 0.f;

    // A for left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        physics.velocity.x = -350.f; // Move left
    }
    // D for right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        physics.velocity.x = 350.f; // Move right
    }

    // Apply physics (gravity handled automatically as acceleration)
    const sf::Vector2f gravity = { 0.f, 98.f }; // Gravity acceleration (m/s^2)
    physics.update(seconds, gravity);

    // Sync sprite with physics (center sprite on physics body)
    sprite->setPosition(physics.position + physics.size / 2.f);
}


void Player::jump(float force) {
    if (physics.isGrounded) {
        physics.velocity.y = JUMP_FORCE;
        physics.isGrounded = false;
    }
}

void Player::draw(sf::RenderTarget& target) const {
    target.draw(*sprite);
}