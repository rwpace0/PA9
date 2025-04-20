#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Entity.hpp"
#include "physics.hpp"

class Player : public Entity {
public:
	Player();

	// sprite movement
	void update(Time dt) override;
	//put sprite on screen
	void draw(RenderTarget & target) const override;
	//jump function
	void jump(float force);

	PhysicsComponent physics; //physics "tag" basically

private:

	void initSprite();
	void initTexture();
	void initStartPos();

	Texture texture; // sprite texture
	Vector2f startPos; // sprite spawn
	const float JUMP_FORCE = -6.f;//give it initial jump force

};
#endif