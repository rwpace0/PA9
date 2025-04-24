#include "Player.hpp"
#include <stdexcept>

Player::Player() : startPos(400.f, 30.f) {
    initTexture();
    initSprite();
    initStartPos();

    if (!healthFont.openFromFile("Fonts/pixelfont.otf")) { 
        throw std::runtime_error("Failed to load health display font");
    }

    healthText = new sf::Text(healthFont, "Health: 100", 24);
    healthText->setFillColor(sf::Color::White);

    //bot left
    healthText->setPosition(Vector2f(20.f, 1100.f)); // 

    
    healthBarBackground.setSize(sf::Vector2f(200.f, 20.f));
    healthBarBackground.setFillColor(sf::Color(100, 100, 100));
    healthBarBackground.setPosition(Vector2f(20.f, 1100.f)); // Above the text

    // init health bar
    healthBar.setSize(sf::Vector2f(200.f, 20.f));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(Vector2f(20.f, 1100.f));

    // Match hitbox to texture size (or scale proportionally)
    auto texSize = texture.getSize();
    physics.size = {
        texSize.x * 0.8f,
        texSize.y * 0.9f
    };

    physics.position = startPos;
}

Player::~Player() {
    delete healthText;
}

void Player::initSprite() {
    sprite.emplace(texture);
    auto texSize = texture.getSize();
    std::cout << "Texture size: " << texSize.x << "x" << texSize.y << std::endl;

    sprite->setOrigin(Vector2(texSize.x / 2.f, texSize.y / 2.f)); // Center origin
}

void Player::initTexture() {
    if (!texture.loadFromFile("Textures/player.png")) {
        throw std::runtime_error("Failed to load player texture, Player.cpp");
    }
}

void Player::initStartPos() {
    sprite->setPosition(startPos);
    physics.position = startPos;
    physics.isPlayer = true;
}

void Player::updateHealthDisplay()
{
    healthText->setString("Health: " + std::to_string(health));

    
    float healthPercentage = static_cast<float>(health) / 100.f;
    healthBar.setSize(sf::Vector2f(200.f * healthPercentage, 20.f));

    
    if (health >= 80) {
        healthBar.setFillColor(sf::Color::Green);
    }
    else if (health >= 20) {
        healthBar.setFillColor(sf::Color::Yellow);
    }
    else {
        healthBar.setFillColor(sf::Color::Red);
    }
}


void Player::draw(sf::RenderTarget& target) const {
    target.draw(*sprite);
    target.draw(healthBarBackground);
    target.draw(healthBar);
    target.draw(*healthText);
}

void Player::reduceHealth(int amount) {
    // Check if the player can take damage
    if (!canTakeDamage()) return;

    health -= amount;
    std::cout << "Player health: " << health << std::endl;

    updateHealthDisplay();

    // Update the last hit time
    lastHitTime = 0.f;

    if (health <= 0) {
        std::cout << "Game Over!" << std::endl;
    }
}

bool Player::canTakeDamage() const {
    return lastHitTime >= hitCooldown;
}

void Player::update(sf::Time dt) {
    const float seconds = dt.asSeconds();

    // Update the last hit time
    lastHitTime += seconds;

    // Jump: W/Space/Up (any of these keys)
    if (physics.isGrounded &&
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))) {
        jump(JUMP_FORCE);
    }

    // Apply physics
    const sf::Vector2f gravity = { 0.f, 980.f };
    physics.update(seconds, gravity);

    // Adjust position based on platform movement when standing still
    if (physics.isGrounded && physics.collidedWithMovingPlatform &&
        !(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))) {
        // Move the player exactly with the platform
        physics.position.x += physics.platformVelocity.x * seconds;
    }

    // Movement: A/Left or D/Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        physics.velocity.x = -350.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        physics.velocity.x = 350.f;
    }
    else {
        physics.velocity.x = 0.f; // Reset velocity if no input
    }

    sprite->setPosition(Vector2(
        physics.position.x + physics.size.x / 2.f,
        physics.position.y + physics.size.y / 2.f
    ));
}




void Player::jump(float force) {
    if (physics.isGrounded) {
        physics.velocity.y = force;
        physics.isGrounded = false;
    }
}

void Player::reset()
{
    health = 100;
    lastHitTime = 0.f;
    updateHealthDisplay();

    physics.position = startPos;
    physics.velocity = { 0.f, 0.f };
    physics.isGrounded = false;
    physics.collidedWithMovingPlatform = false;
    physics.platformVelocity = { 0.f, 0.f };

    // Reset sprite position
    if (sprite.has_value()) {
        sprite->setPosition(Vector2(
            physics.position.x + physics.size.x / 2.f,
            physics.position.y + physics.size.y / 2.f
        ));
    }
}
