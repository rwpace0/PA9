#include "physics.hpp"

bool Physics::AABB(const sf::FloatRect& a, const sf::FloatRect& b) {
    return a.findIntersection(b).has_value();
}

void Physics::resolveCollision(PhysicsComponent& dynamic, const sf::FloatRect& staticObj, const sf::Vector2f& staticObjVelocity) {
    const sf::FloatRect dynBounds = dynamic.getBounds();
    std::optional<sf::FloatRect> overlap = dynBounds.findIntersection(staticObj);

    if (!overlap) return;

    // Reset collision flags
    dynamic.collidedWithProjectile = false;
    dynamic.collidedWithMovingPlatform = false;

    const sf::Vector2f dynPos = dynBounds.position;
    const sf::Vector2f dynSize = dynBounds.size;
    const sf::Vector2f staticPos = staticObj.position;
    const sf::Vector2f staticSize = staticObj.size;

    const float overlapLeft = (dynPos.x + dynSize.x) - staticPos.x;
    const float overlapRight = (staticPos.x + staticSize.x) - dynPos.x;
    const float overlapTop = (dynPos.y + dynSize.y) - staticPos.y;
    const float overlapBottom = (staticPos.y + staticSize.y) - dynPos.y;

    const float minX = std::min(overlapLeft, overlapRight);
    const float minY = std::min(overlapTop, overlapBottom);

    if (staticObjVelocity != sf::Vector2f(0, 0)) {
        dynamic.collidedWithMovingPlatform = true;
        dynamic.platformVelocity = staticObjVelocity;

        // Match the player's velocity with the platform's velocity
        if (dynamic.isPlayer) {
            dynamic.velocity += staticObjVelocity;
        }
    }

    if (minX < minY) {
        dynamic.position.x += (overlapLeft < overlapRight) ? -overlapLeft : overlapRight;
        dynamic.velocity.x = 0;
    }
    else {
        dynamic.position.y += (overlapTop < overlapBottom) ? -overlapTop : overlapBottom;
        dynamic.velocity.y = 0;
        dynamic.isGrounded = (overlapTop < overlapBottom);
    }
}