#pragma once
#include "Entity.hpp"
#include "physics.hpp"

class Player : public Entity {
public:
    Player();
    ~Player();

    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) const override;
    void jump(float force);
    void reset();

    // Health-related methods
    void reduceHealth(int amount);
    int getHealth() const { return health; }
    bool isDead() const { return health <= 0; }

    // Cooldown-related methods
    bool canTakeDamage() const;

    PhysicsComponent physics;

private:
    void initSprite();
    void initTexture();
    void initStartPos();

    sf::Texture texture;
    std::optional<sf::Sprite> sprite;
    sf::Vector2f startPos;
    const float JUMP_FORCE = -800.f;

    sf::Font healthFont;
    sf::Text* healthText;
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBar;
    void updateHealthDisplay();

    int health = 100; // Player starts with 100 health
    float lastHitTime = 0.f; // Time since the last hit
    const float hitCooldown = 1.f; // Cooldown duration in seconds
};
