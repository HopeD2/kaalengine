#pragma once

#include <SFML/Graphics.hpp>

#include "Character.h"
#include "Collider.h"

namespace kaal {
	class ColliderComponent
	{
	public:
		ColliderComponent(sf::RectangleShape const& _body, Character & _owner, sf::Vector2f _posOffsetFromOwner, bool show = false);
		~ColliderComponent();
		sf::RectangleShape& getBody();
		Character& getOwner();
		void setPosition(sf::Vector2f newPos);
		sf::Vector2f getPositionOffset() const;

		void update(float deltaTime);
		void draw(sf::RenderWindow &renderWindow);
		CollisionDirection collisionDir;
	private:
		Character &owner;
		sf::RectangleShape body;
		sf::Vector2f posOffsetFromOwner;
	};
}

