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

    /* -- SFML 3.0+ PROPER RECTANGLE HANDLING -- */
    const sf::Vector2f dynPos = dynBounds.position;
    const sf::Vector2f dynSize = dynBounds.size;
    const sf::Vector2f staticPos = staticObj.position;
    const sf::Vector2f staticSize = staticObj.size;

    // Calculate overlap depths using SFML 3.0 methods
    const float overlapLeft = (dynPos.x + dynSize.x) - staticPos.x;
    const float overlapRight = (staticPos.x + staticSize.x) - dynPos.x;
    const float overlapTop = (dynPos.y + dynSize.y) - staticPos.y;
    const float overlapBottom = (staticPos.y + staticSize.y) - dynPos.y;

    // Find minimum penetration
    const float minX = std::min(overlapLeft, overlapRight);
    const float minY = std::min(overlapTop, overlapBottom);

    // Collision type detection (before resolution)
    if (/* projectile check */ false) {  // Replace with your projectile condition
        dynamic.collidedWithProjectile = true;
        return;
    }
    else if (staticObjVelocity != sf::Vector2f(0, 0)) {
        dynamic.collidedWithMovingPlatform = true;
        dynamic.platformVelocity = staticObjVelocity;
    }

    // Resolution along axis of least penetration
    if (minX < minY) {
        // Horizontal collision
        dynamic.position.x += (overlapLeft < overlapRight) ? -overlapLeft : overlapRight;
        dynamic.velocity.x = 0;
    }
    else {
        // Vertical collision
        dynamic.position.y += (overlapTop < overlapBottom) ? -overlapTop : overlapBottom;
        dynamic.velocity.y = 0;
        dynamic.isGrounded = (overlapTop < overlapBottom);
    }
}

void Physics::drawDebug(sf::RenderTarget& target, const PhysicsComponent& phys) {
    target.draw(phys.getDebugShape());
}