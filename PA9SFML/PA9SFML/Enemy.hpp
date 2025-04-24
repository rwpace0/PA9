#pragma once
#ifndef ENEMY
#define ENEMY

#include "Entity.hpp"




class Enemy : public Entity
{
public:

    Enemy();

    ~Enemy() = default;

    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) const override;

    //setter
    void setSpeed(float speed);
    void setPosition(float x, float y);

    sf::Vector2f getSize() const;
    sf::FloatRect getBounds() const;


private:

    void initTexture();
    void initSprite();

    sf::Vector2f startPos;
	sf::RectangleShape shape;
	float moveSpeed;

    Texture texture;
    Sprite sprite;
};


#endif // !ENEMY