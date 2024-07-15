#include "ColliderComponent.h"

kaal::ColliderComponent::ColliderComponent(sf::RectangleShape const& _body, Character& _owner, sf::Vector2f _posOffsetFromOwner, bool show) :
	body(_body),
	owner(_owner),
	posOffsetFromOwner(_posOffsetFromOwner),
	collisionDir(kaal::CollisionDirection::NO_COL)
{
	body.setFillColor(sf::Color::Transparent);
	body.setPosition(body.getPosition() + _posOffsetFromOwner);

	if (show)
	{
		body.setOutlineColor(sf::Color::Red);
		body.setOutlineThickness(2.f);
	}
}

kaal::ColliderComponent::~ColliderComponent()
{
}

sf::RectangleShape & kaal::ColliderComponent::getBody()
{
	return this->body;
}

kaal::Character & kaal::ColliderComponent::getOwner()
{
	return this->owner;
}

void kaal::ColliderComponent::setPosition(sf::Vector2f newPos)
{
	this->body.setPosition(newPos);
}

sf::Vector2f kaal::ColliderComponent::getPositionOffset() const
{
	return this->posOffsetFromOwner;
}

void kaal::ColliderComponent::update(float deltaTime)
{
}

void kaal::ColliderComponent::draw(sf::RenderWindow & renderWindow)
{
	renderWindow.draw(body);
}
