#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "ColliderComponent.h"
#include "Character.h"

namespace kaal {
	class Player : public Character
	{
	public:
		Player() = delete;
		Player(sf::Vector2f size, sf::Texture *_texture, sf::Vector2u _imageCount, float _switchTime, float speed);
		~Player();

		void update(float deltaTime, sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);

		sf::RectangleShape & getBody() override;
		sf::RectangleShape & getCollisionBox();
		ColliderComponent& getColliderComponent();
		sf::Vector2f & getVelocity();

		void setLevelOffset(sf::Vector2f offset);

	private:
		sf::RectangleShape body;
		ColliderComponent collisionBox;
		Animation animation;
		sf::Vector2f acceleration;
		bool faceRight;
		float speed;
		sf::Vector2f velocity;
		bool isJumping;
		bool isDashing;
		sf::Vector2f finalVelocity;
		sf::Vector2f finalDashPos;
		float currentVelocityY;
		float totalDistanceTravelled;
		float dashTimeout;
		float dashDistance;
		sf::Clock timer;
		float mass;
		float dashForce;
		sf::Vector2f *lastDash;
		sf::Vector2f levelOffset;
	};
}

