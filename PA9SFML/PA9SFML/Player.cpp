#include "Player.hpp"
#include <stdexcept>

Player::Player() : startPos(400.f, 30.f) {
    initTexture();
    initSprite();
    initStartPos();

    // Match hitbox to texture size (or scale proportionally)
    auto texSize = texture.getSize();
    physics.size = {
        texSize.x * 0.8f,
        texSize.y * 0.9f
    };

    physics.position = startPos;
}

void Player::initSprite() {
    sprite.emplace(texture);
    auto texSize = texture.getSize();
    std::cout << "Texture size: " << texSize.x << "x" << texSize.y << std::endl;

    sprite->setOrigin(Vector2(texSize.x / 2.f, texSize.y / 2.f)); // Center origin
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

void Player::draw(sf::RenderTarget& target) const {
    target.draw(*sprite); // Draw actual sprite
    Physics::drawDebug(target, physics); // Draw hitbox (red)
}

void Player::update(sf::Time dt) {
    const float seconds = dt.asSeconds();

    // Reset horizontal velocity
    physics.velocity.x = 0.f;

    // Movement: A/Left or D/Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        physics.velocity.x = -350.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        physics.velocity.x = 350.f;
    }

    // Jump: W/Space/Up (any of these keys)
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)))) {
        jump(JUMP_FORCE);
    }

    // Apply physics
    const sf::Vector2f gravity = { 0.f, 980.f }; // Stronger gravity for snappy jumps
        physics.update(seconds, gravity);

        sprite->setPosition(Vector2(
            physics.position.x + physics.size.x / 2.f,  // X: hitbox center
            physics.position.y + physics.size.y / 2.f   // Y: hitbox center
        ));
}

void Player::jump(float force) {
    if (physics.isGrounded) {
        physics.velocity.y = force;
        physics.isGrounded = false;
    }
}

// ... (keep existing initSprite(), initTexture(), initStartPos(), draw())