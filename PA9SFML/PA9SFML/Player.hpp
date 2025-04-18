#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Entity.hpp"

class Player : public Entity {
public:
	Player();

	void handleInput();
	void update(Time dt) override;
	void draw(RenderTarget & target) const override;

	//Animation

	//Movement

	//core

private:
	void initSprite();
	void initTexture();
	void initStartPos();

	Texture texture;
	Vector2f startPos;
	
};
#endif