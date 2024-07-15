#pragma once

#include <SFML/Graphics.hpp>

class Line
{
public:
	Line(sf::Vector2f pt1, sf::Vector2f pt2);
	~Line() = default;
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
private:
	sf::Vector2f pt1;
	sf::Vector2f pt2;
};

