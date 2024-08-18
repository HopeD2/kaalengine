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
	isDashing(false),
	collisionBox(sf::RectangleShape(sf::Vector2f(64.f, 64.f)),*this, size / 4.f, true),
	finalVelocity(0.f, 0000.f),
	currentVelocityY(0.f),
	totalDistanceTravelled(0.f),
	dashTimeout(0.8f),
	dashDistance(300.f),
	mass(5000.f),
	dashForce(10.f),
	levelOffset(0.f,0.f)
{
	body.setFillColor(sf::Color::Cyan);

	if (_texture) {
		body.setTexture(_texture);
	}
}

kaal::Player::~Player()
{
}

void kaal::Player::update(float deltaTime, sf::RenderWindow& window)
{
	int row = 0;
	int stopAt = 7;
	bool isIdle = true;

	if (!isDashing)
	{
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
	}

	sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
	mousePos += levelOffset;
	sf::Vector2f dashVec = mousePos -  (body.getPosition() + body.getSize() / 2.f);
	dashVec = kaal::utility::getSignVector(dashVec);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && !isDashing && timer.getElapsedTime().asSeconds() >= dashTimeout)
	{
		dashVec = kaal::utility::getSignVector(dashVec);
		if (!lastDash) {
			lastDash = new sf::Vector2f(dashVec);
		}
		float acceleration = mass / dashForce;
		velocity = dashVec * sqrtf(2.0f * acceleration * 1000.f);
		//dashTimeout = 1.5f;
		isDashing = true;
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
		//isDashing = false;
	}

	if (collisionBox.collisionDir == kaal::UP && isDashing)
	{
		if (lastDash) {
			dashVec.y = -lastDash->y;
			timer.restart();
			totalDistanceTravelled = 0;
			float acceleration = mass / dashForce;
			velocity = dashVec * sqrtf(2.0f * acceleration * 1000.f);
			isDashing = true;
			lastDash = nullptr;
		}
		else {
			lastDash = nullptr;
			isDashing = false;
			totalDistanceTravelled = dashDistance;
		}
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

	if (isDashing)
	{
		row = 6;
		stopAt = 1;
	}

	animation.update(row, deltaTime, stopAt, faceRight);
	body.setTextureRect(animation.uvRect);

	sf::Vector2f moveby = velocity * deltaTime;

	if (isDashing) {
		totalDistanceTravelled += std::sqrt(moveby.x * moveby.x + moveby.y * moveby.y);
	}

	if (totalDistanceTravelled >= dashDistance) {
		isDashing = false;
		lastDash = nullptr;
		totalDistanceTravelled = 0.f;
		velocity.y = 0.f;
		timer.restart();
	}

	body.move(moveby);
	collisionBox.getBody().move(moveby);
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

void kaal::Player::setLevelOffset(sf::Vector2f offset)
{
	// TODO: Change later, should not be managed by player
	levelOffset = offset;
}
