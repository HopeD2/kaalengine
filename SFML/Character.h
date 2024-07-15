#pragma once

#include <SFML/Graphics.hpp>

namespace kaal {
	class Character 
	{
	public:
		virtual sf::RectangleShape& getBody() = 0;
	};
}