#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "Header.hpp"

class Entity {
public:
	
	Entity() : velocity(0.f, 0.f) {}
	virtual ~Entity() = default;
	virtual void update(Time dt) = 0;
	virtual void draw(RenderTarget& target) const = 0;
	
protected:
	//optional makes sprite a pointer
	optional<Sprite> sprite;
	//velocity of the movement
	Vector2f velocity;
};

#endif