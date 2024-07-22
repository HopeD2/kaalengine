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
	dashTimeout(1.5f),
	dashDistance(300.f)
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
	sf::Vector2f dashVec = mousePos -  body.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && !isDashing && timer.getElapsedTime().asSeconds() >= dashTimeout)
	{
		std::cout << "Dash\n";
		dashVec = kaal::utility::getSignVector(dashVec);
		float acc = 5000.f / 5.f;
		velocity = dashVec * sqrtf(2.0f * acc * 1000.f);
		finalVelocity = velocity;
		finalDashPos = body.getPosition() + sf::Vector2f(100.f,100.f);
		kaal::utility::dispVector(finalDashPos);
		std::cout << "\n";
		isDashing = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !isJumping)
	{
		std::cout << "Jump!\n";
		velocity.y = - sqrtf(2.0f * 981.f * 100.f);
		isJumping = true;
	}


	velocity.y += 981.f * deltaTime;
	if (collisionBox.collisionDir == kaal::DOWN)
	{
		isJumping = false;
		velocity.y = 0.f;
		isDashing = false;
	}

	if (isDashing)
	{
		kaal::utility::dispVector(velocity);
		std::cout << "\n";
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

	sf::Vector2f moveby = velocity * deltaTime;

	if (isDashing) {
		totalDistanceTravelled += std::sqrt(moveby.x * moveby.x + moveby.y * moveby.y);
	}

	if (totalDistanceTravelled >= dashDistance) {
		isDashing = false;
		totalDistanceTravelled = 0.f;
		std::cout << "Dashing stopped\n";
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
