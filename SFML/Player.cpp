#include "Player.h"
#include "Utility.h"
#include "ColliderComponent.h"

#include <iostream>

kaal::Player::Player(sf::Vector2f size, sf::Texture * _texture, sf::Vector2u _imageCount, float _switchTime, float _speed) :
	body(size),
	animation(_texture, _imageCount, _switchTime),
	speed(_speed),
	faceRight(true),
	isJumping(false),
	collisionBox(sf::RectangleShape(sf::Vector2f(64.f, 64.f)),*this, size / 4.f, true),
	finalVelocity(0.f),
	currentVelocityY(0.f)
{
	body.setFillColor(sf::Color::Cyan);

	if (_texture) {
		body.setTexture(_texture);
	}
}

kaal::Player::~Player()
{
}

void kaal::Player::update(float deltaTime)
{
	int row = 0;
	bool isIdle = true;

	velocity.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		velocity.x -= (speed);
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		velocity.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		velocity.y -= 1;
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		velocity.x += (speed);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !isJumping)
	{
		velocity.y = - sqrtf(2.0f * 981.f * 100.f);
		isJumping = true;
	}

	velocity.y += 981.f * deltaTime;
	if (collisionBox.collisionDir == kaal::DOWN)
	{
		isJumping = false;
		velocity.y = 0.f;
	}

	if (velocity.x != 0.f)
	{
		row = 1;
	}

	if (velocity.x < 0.f)
	{
		faceRight = false;
	}
	else if (velocity.x > 0.f)
	{
		faceRight = true;
	}

	animation.update(row, deltaTime, 7, faceRight);
	body.setTextureRect(animation.uvRect);

	body.move(velocity * deltaTime);
	collisionBox.getBody().move(velocity * deltaTime);
}

void kaal::Player::draw(sf::RenderWindow& window)
{
	collisionBox.draw(window);
	window.draw(body);
}

sf::RectangleShape& kaal::Player::getBody()
{
	return body;
}

sf::RectangleShape & kaal::Player::getCollisionBox()
{
	return collisionBox.getBody();
}

kaal::ColliderComponent& kaal::Player::getColliderComponent()
{
	return collisionBox;
}

sf::Vector2f & kaal::Player::getVelocity()
{
	return velocity;
}
