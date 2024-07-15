// SFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Player.h"
#include "Utility.h"
#include "Collider.h"

const float VIEW_WIDTH = 1024.f;
const float VIEW_HEIGHT = 768.f;

// Define the element-wise multiplication operator for sf::Vector2f
sf::Vector2f operator*(const sf::Vector2f& left, const sf::Vector2f& right)
{
	return sf::Vector2f(left.x * right.x, left.y * right.y);
}

void ResizeView(sf::RenderWindow& window, sf::View& view)
{
	float windowRatio = float(window.getSize().x) / float(window.getSize().y);
	float viewRatio = float(view.getSize().x) / float(view.getSize().y);

	float newWidth = 1.f;
	float newHeight = 1.f;

	if (windowRatio > 1.f)
	{
		newWidth = viewRatio / windowRatio;
	}
	else
	{
		newHeight = windowRatio / viewRatio;
	}

	view.setViewport(sf::FloatRect((1.f - newWidth)/2, (1.f - newHeight)/2,  newWidth, newHeight));
	view.setCenter(view.getSize() / 2.f);
}

bool IsPointInRectangle(sf::Vector2i point, sf::RectangleShape shape)
{

	return ((point.x >= shape.getPosition().x) && (point.x <= (shape.getPosition().x + shape.getSize().x))
		&& (point.y >= shape.getPosition().y) && (point.y <= (shape.getPosition().y + shape.getSize().y)));
}

bool AreRectanglesOverlapping(sf::RectangleShape rect1, sf::RectangleShape rect2)
{
	return ((rect1.getPosition().x < rect2.getPosition().x + rect2.getSize().x) && (rect1.getPosition().x + rect1.getSize().x > rect2.getPosition().x) &&
		(rect1.getPosition().y < rect2.getPosition().y + rect2.getSize().y) && (rect1.getPosition().y + rect1.getSize().y > rect2.getPosition().y));
}		

int main()
{
	sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "TheGame", sf::Style::Default);
	sf::RectangleShape playerCollisionBox(sf::Vector2f(64.f,64.f));
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	sf::Texture playerTexture;
	playerTexture.loadFromFile("../resources/DarkSamuraiAssets/DarkSamurai.png");

	kaal::Player player{ sf::Vector2f(128.f, 128.f), &playerTexture, sf::Vector2u(14, 8), (float) 0.1, 250.f };
	

	sf::RectangleShape wall = kaal::utility::GetCustomRectangle(sf::Vector2f(256.f, 256.f), sf::Vector2f(0.f, 450.f), 2.f, sf::Color::Magenta, sf::Color::Transparent);
	sf::RectangleShape wall2 = kaal::utility::GetCustomRectangle(sf::Vector2f(256.f, 256.f), sf::Vector2f(wall.getPosition().x + wall.getSize().x, wall.getPosition().y), 2.f, sf::Color::Magenta, sf::Color::Transparent);
	sf::RectangleShape wall3 = kaal::utility::GetCustomRectangle(sf::Vector2f(800.f, 256.f), sf::Vector2f(wall2.getPosition().x + wall2.getSize().x, wall2.getPosition().y - 50.f), 2.f, sf::Color::Magenta, sf::Color::Transparent);

	std::vector<sf::RectangleShape> platforms;
	platforms.emplace_back(wall);
	platforms.emplace_back(wall2);
	platforms.emplace_back(wall3);

	sf::Clock clock;
	view.setCenter(VIEW_WIDTH / 2, VIEW_HEIGHT / 2);

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		// temporary fix
		if (deltaTime > 0.001)
		{
			deltaTime = 0.001;
		}

		sf::Event evt;
		while (window.pollEvent(evt)) 
		{
			switch (evt.type)
			{
				case sf::Event::Closed:
				{
					window.close();
				}break;
				case sf::Event::Resized:
				{
					ResizeView(window, view);
				}break;
			}
		}

		auto mousePos = sf::Mouse::getPosition(window);

		sf::Vector2f playerPos = (player.getBody().getSize() - player.getBody().getPosition()) / 2.f;
		sf::RectangleShape& playerRect = player.getCollisionBox();

		for (auto &platform : platforms)
		{
			auto colDir = kaal::Collider::ResolveCollision(player.getColliderComponent(), platform, 0.f);
			if (colDir != kaal::NO_COL) {
				break;
			}
		}
		
		player.update(deltaTime);

		view.setCenter(player.getBody().getPosition());
		window.clear(sf::Color::Black);
		window.setView(view);

		// Clear the viewport area with the desired color
		sf::RectangleShape viewportBackground;
		viewportBackground.setSize(sf::Vector2f(view.getSize().x, view.getSize().y));
		viewportBackground.setFillColor(sf::Color::Color(128, 128, 128)); // Set your desired color here
		viewportBackground.setOrigin((viewportBackground.getPosition() + viewportBackground.getSize())/2.f);
		viewportBackground.setPosition(player.getBody().getPosition());
		window.draw(viewportBackground);
		for (auto &platform : platforms)
		{
			window.draw(platform);
		}
		player.draw(window);
		window.display();

	//	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return 0;
}


