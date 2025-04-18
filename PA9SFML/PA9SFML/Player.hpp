#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Entity.hpp"

class Player : public Entity {
public:
	Player();

	// sprite movement
	void update(Time dt) override;
	//put sprite on screen
	void draw(RenderTarget & target) const override;

private:

	void initSprite();
	void initTexture();
	void initStartPos();

	Texture texture; // sprite texture
	Vector2f startPos; // sprite spawn

};
#endif