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

		void update(float deltaTime);
		void draw(sf::RenderWindow& window);

		sf::RectangleShape & getBody() override;
		sf::RectangleShape & getCollisionBox();
		ColliderComponent& getColliderComponent();
		sf::Vector2f & getVelocity();
	public:
		//bool isColliding;

	private:
		sf::RectangleShape body;
		ColliderComponent collisionBox;
		Animation animation;
		sf::Vector2f acceleration;
		bool faceRight;
		float speed;
		//sf::RectangleShape collisionBox;
		sf::Vector2f velocity;
		bool isJumping;
		float finalVelocity;
		float currentVelocityY;
	};
}

