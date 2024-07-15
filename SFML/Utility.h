#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace kaal {
	namespace utility {
		static sf::Vector2f normalize(const sf::Vector2f& source) {
			float length = std::sqrt(source.x * source.x + source.y * source.y);
			if (length != 0) {
				return sf::Vector2f(source.x / length, source.y / length);
			}
			else {
				return source; // Or handle the zero vector case as needed
			}
		}


		template <typename T>
		void dispVector(T vector)
		{
			std::cout << "(" << vector.x << "," << vector.y << ")";
		}


		// Function to get the sign of a float
		static float sign(float value)
		{
			if (value > 0)
				return 1.f;
			else if (value < 0)
				return -1.f;
			else
				return 0.f; // Could also return 1 or -1 depending on the use case
		}

		// Function to get the sign vector of an sf::Vector2f
		static sf::Vector2f getSignVector(const sf::Vector2f& vec)
		{
			return sf::Vector2f(sign(vec.x), sign(vec.y));
		}

		static sf::RectangleShape GetCustomRectangle(
			sf::Vector2f size,
			sf::Vector2f location,
			float outlineThickness = 2.f,
			sf::Color outlineColor = sf::Color::Red,
			sf::Color fillColor = sf::Color::White
		)
		{
			sf::RectangleShape shape(size);
			shape.setFillColor(fillColor);
			shape.setOutlineColor(outlineColor);
			shape.setOutlineThickness(outlineThickness);
			shape.move(location);

			return shape;
		}
	}
}
