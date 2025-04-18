#include "Player.hpp"

Player::Player() : startPos(400.f, 300.f)  //spawn point
{
	initTexture();
	initSprite();
	initStartPos();
}

void Player::initSprite()
{
	sprite.emplace(texture);
}

void Player::initTexture()
{
	if (!texture.loadFromFile("Textures/player_walk_2.png"))
		throw runtime_error("Failed to load player texture");
}

void Player::initStartPos()
{
	sprite->setPosition(startPos);	
}


void Player::handleInput()
{

}

void Player::update(Time dt)
{
	handleInput();

}

void Player::draw(RenderTarget& target) const
{
	target.draw(*sprite);
}

