#include "Enemy.hpp"


Enemy::Enemy()
{

	startPos = sf::Vector2f(-50.f, static_cast<float>(rand() % 500));
	moveSpeed = 300.f; //speed of object
	shape.setSize(sf::Vector2f(80.f, 50.f)); //mess with the size of rectangle
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(startPos);

}

void Enemy::update(sf::Time dt)
{
	float deltaTime = dt.asSeconds();

	shape.move(sf::Vector2f(moveSpeed * deltaTime, 0.f));

	if (shape.getPosition().x > 2000.f)
	{
		shape.setPosition(sf::Vector2f( - shape.getSize().x, rand() % 500));

	}

}

void Enemy::draw(sf::RenderTarget& target) const
{
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

void Enemy::setPosition(float x, float y)
{
	shape.setPosition(sf::Vector2f(x, y));
}