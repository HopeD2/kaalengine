#pragma once

#include <SFML/Graphics.hpp>

namespace kaal 
{
	class ColliderComponent;

	enum CollisionDirection {
		NO_COL,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	class Collider
	{
	public:
		Collider() = default;
		~Collider() = default;
		Collider(sf::RectangleShape& _rect1, sf::RectangleShape& _rect2);
		static bool AreRectanglesColliding(sf::RectangleShape rect1, sf::RectangleShape rect2);
		static CollisionDirection ResolveCollision(sf::RectangleShape &rect1, sf::RectangleShape &rect2, float push);
		static CollisionDirection ResolveCollision(ColliderComponent &collidercmp, sf::RectangleShape &rect2, float push);

		void update(float deltaTime);
		void draw(sf::RenderWindow& window);
	private:
		sf::RectangleShape& rect1;
		sf::RectangleShape& rect2;
	};
}

