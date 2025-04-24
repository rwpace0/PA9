#include "Enemy.hpp"
#include <iostream>


Enemy::Enemy()
{

	startPos = sf::Vector2f(-50.f, static_cast<float>(rand() % 500));
	moveSpeed = 300.f; //speed of object

	initTexture();

	initSprite();

	shape.setSize(sf::Vector2f(80.f, 50.f)); //mess with the size of rectangle
	shape.setFillColor(sf::Color::Transparent);
	shape.setPosition(startPos);

}

void Enemy::initTexture() {

	if (!texture.loadFromFile("Beagle_sprite.png")) {
		std::cout << "ERROR::Enemy::file not loaded" << std::endl;
	}


}

void Enemy::initSprite() {

	sprite.setTexture(texture);

	sf::Vector2u textsize = texture.getSize();

	sprite.setOrigin(textsize.x/2.f, textsize.y / 2.f);


	sprite.setPosition(startPos.x + shape.getSize().x / 2.f, startPos.y +
		shape.getSize().y / 2.f);

}

void Enemy::update(sf::Time dt)
{
	float deltaTime = dt.asSeconds();

	shape.move(sf::Vector2f(moveSpeed * deltaTime, 0.f));

	sprite.setPosition(shape.getPosition().x + shape.getSize().x /2.f,
		shape.getPosition().y + shape.getSize().y / 2.f);


	if (shape.getPosition().x > 2000.f)
	{
		sf::Vector2f newPos = sf::Vector2f(-shape.getSize().x, rand() % 500);
		shape.setPosition(newPos);
		sprite.setPosition(newPos.x + shape.getSize().x / 2.f,
			newPos.y + shape.getSize().y/2.f);

	}

}

void Enemy::draw(sf::RenderTarget& target) const
{
	target.draw(sprite);
	target.draw(shape);
}

void Enemy::setSpeed(float speed)
{
	moveSpeed = speed;
}

sf::Vector2f Enemy::getSize() const
{
	return shape.getSize();
}

sf::FloatRect Enemy::getBounds() const {
	return sf::FloatRect(shape.getPosition(), shape.getSize());
}

void Enemy::setPosition(float x, float y)
{

	shape.setPosition(sf::Vector2f(x, y));

	

	sprite.setPosition(x + shape.getSize().x / 2.f,
		y + shape.getSize().y / 2.f);

	
}