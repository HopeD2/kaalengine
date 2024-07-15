#include "Collider.h"
#include "Utility.h"
#include "ColliderComponent.h"

kaal::Collider::Collider(sf::RectangleShape& _rect1, sf::RectangleShape& _rect2): 
	rect1(_rect1),
	rect2(_rect2)
{
}

bool kaal::Collider::AreRectanglesColliding(sf::RectangleShape rect1, sf::RectangleShape rect2)
{
	return ((rect1.getPosition().x < rect2.getPosition().x + rect2.getSize().x) && (rect1.getPosition().x + rect1.getSize().x > rect2.getPosition().x) &&
		(rect1.getPosition().y < rect2.getPosition().y + rect2.getSize().y) && (rect1.getPosition().y + rect1.getSize().y > rect2.getPosition().y));
}

kaal::CollisionDirection kaal::Collider::ResolveCollision(sf::RectangleShape &rect1, sf::RectangleShape &rect2, float push)
{
	bool areColliding = AreRectanglesColliding(rect1, rect2);
	
	CollisionDirection direction = NO_COL;

	if (areColliding)
	{
		auto rect1Position = rect1.getPosition();
		auto rect1Size = rect1.getSize();

		auto rect2Position = rect2.getPosition();
		auto rect2Size = rect2.getSize();

		auto tempDiffX = std::abs(rect2Position.x - (rect1Position.x + rect1Size.x));
		auto tempDiffXS = std::abs(rect2Position.x + rect2Size.x - (rect1Position.x));
		auto tempDiffY = std::abs(rect2Position.y - (rect1Position.y + rect1Size.y));
		auto tempDiffYS = std::abs(rect2Position.y + rect2Size.y - (rect1Position.y));

		float min = std::min(std::min(tempDiffX, tempDiffY), std::min(tempDiffXS, tempDiffYS));

		if (min == tempDiffX)
		{
			//Left
			float diff = std::abs(rect2Position.x - (rect1Position.x + rect1Size.x));
			rect1.move(sf::Vector2f(-diff, 0.f));
			direction = CollisionDirection::LEFT;
		}
		else if (min == tempDiffXS)
		{
			//Right
			float diff = std::abs(rect2Position.x + rect2Size.x - (rect1Position.x));
			rect1.move(sf::Vector2f(diff, 0.f));
			direction = CollisionDirection::RIGHT;
		//	std::cout << "RIGHT\n";
		}
		else if (min == tempDiffY)
		{
			//Top
			float diff = std::abs(rect2Position.y - (rect1Position.y + rect1.getSize().y));
			rect1.move(sf::Vector2f(0.f, -diff));
	//		std::cout << "DOWN\n";
			direction = CollisionDirection::DOWN;
		}
		else if (min == tempDiffYS)
		{
			//Bottom
			float diff = std::abs(rect2Position.y + rect2Size.y - (rect1Position.y));
			rect1.move(sf::Vector2f(0.f, diff));
	//		std::cout << "UP\n";
			direction = CollisionDirection::UP;
		}

		rect2.setOutlineColor(sf::Color::Green);
	}
	else {
		rect2.setOutlineColor(sf::Color::Magenta);
	}

	return direction;
}

	
kaal::CollisionDirection kaal::Collider::ResolveCollision(ColliderComponent &collidercmp, sf::RectangleShape & rect2, float push) 
{
	auto& rect1 = collidercmp.getBody();
	auto& ownerBody = collidercmp.getOwner().getBody();

	collidercmp.collisionDir = ResolveCollision(rect1, rect2, push);

	if (collidercmp.collisionDir != kaal::CollisionDirection::NO_COL)
	{
		ownerBody.move(rect1.getPosition() - collidercmp.getPositionOffset() - ownerBody.getPosition());
	}

	return collidercmp.collisionDir;
}

void kaal::Collider::update(float deltaTime)
{
}

void kaal::Collider::draw(sf::RenderWindow & window)
{
}
