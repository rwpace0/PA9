#include "Player.hpp"

Player::Player() : startPos(400.f, 300.f)  //player spawn point
{
	initTexture();
	initSprite();
	initStartPos();
}

void Player::initSprite()
{
	sprite.emplace(texture);//puts the texture onto the sprite
}

void Player::initTexture()
{
	//loads the sprite texture from file
	if (!texture.loadFromFile("Textures/player_walk_2.png"))
		throw runtime_error("Failed to load player texture");
}

void Player::initStartPos()
{
	sprite->setPosition(startPos); //sprite spawn point on screen	
}

void Player::update(Time dt)
{

	float seconds = dt.asSeconds();
	const float speed = 200.f;

	//reset velocity every time the key is released so there is no gliding
	velocity.x = 0.f;

	// A for left
	if (Keyboard::isKeyPressed(Keyboard::Scan::A) || Keyboard::isKeyPressed(Keyboard::Scan::Left)) {
		velocity.x = -speed; // move 200 px/fps in the left
	}
	// D for right
	if (Keyboard::isKeyPressed(Keyboard::Scan::D) || Keyboard::isKeyPressed(Keyboard::Scan::Right)) {
		velocity.x = +speed;
	}
	
	//move the sprite at px/s
	sprite->move(velocity * seconds);
}

void Player::draw(RenderTarget& target) const
{
	target.draw(*sprite);//display sprite to screen
}

