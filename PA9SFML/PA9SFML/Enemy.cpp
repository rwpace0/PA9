#include "Enemy.hpp"
#include <iostream>

sf::Texture Enemy::texture;
Enemy::Enemy()
{
	initTexture();
	initSprite();
	startPos = sf::Vector2f(-50.f, static_cast<float>(rand() % 500));
	moveSpeed = 300.f; //speed of object

	

	shape.setSize(sf::Vector2f(80.f, 50.f)); //mess with the size of rectangle
	shape.setFillColor(sf::Color::Transparent);
	shape.setPosition(startPos);

	

	
	auto texSize = texture.getSize();
	shape.setSize({
	texSize.x * 0.8f,
	texSize.y * 0.9f
	});
}

void Enemy::initTexture() {

	static bool textureLoaded = false;
	if (!textureLoaded) {
		if (!texture.loadFromFile("Textures/beagle.png")) {
			throw std::runtime_error("Failed to load enemy texture, Enemy.cpp");
			return;
		}
		textureLoaded = true;
		std::cout << "Enemy texture loaded successfully" << std::endl;
	}

}

void Enemy::initSprite() {

	sprite.emplace(texture);
	auto texSize = texture.getSize();
	std::cout << "Texture size: " << texSize.x << "x" << texSize.y << std::endl;

	sprite->setOrigin(Vector2f(texSize.x / 2.f, texSize.y / 2.f)); // Center origin

}

void Enemy::update(sf::Time dt)
{
	float deltaTime = dt.asSeconds();

	shape.move(sf::Vector2f(moveSpeed * deltaTime, 0.f));

	// Use arrow operator for optional<Sprite>
	sprite->setPosition(sf::Vector2f(
		shape.getPosition().x + shape.getSize().x / 2.f,
		shape.getPosition().y + shape.getSize().y / 2.f
	));

	if (shape.getPosition().x > 2000.f) {
		sf::Vector2f newPos = sf::Vector2f(-shape.getSize().x, rand() % 500);
		shape.setPosition(newPos);
		sprite->setPosition(sf::Vector2f(
			newPos.x + shape.getSize().x / 2.f,
			newPos.y + shape.getSize().y / 2.f
		));
	}
}

void Enemy::draw(sf::RenderTarget& target) const
{
	
	target.draw(*sprite);
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

	
	sprite->setPosition(sf::Vector2f(
		x + shape.getSize().x / 2.f,
		y + shape.getSize().y / 2.f
	));
	
}