#pragma once
#include "Entity.hpp"
#include "physics.hpp"

class Player : public Entity {
public:
    Player();

    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) const override;
    void jump(float force);

    PhysicsComponent physics;

private:
    void initSprite();
    void initTexture();
    void initStartPos();

    sf::Texture texture;
    std::optional<sf::Sprite> sprite;
    sf::Vector2f startPos;
    const float JUMP_FORCE = -600.f;
};