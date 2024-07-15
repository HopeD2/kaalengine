#pragma once

#include <SFML/Graphics.hpp>

namespace kaal 
{
	class Animation
	{
	public:
		Animation() = delete;
		Animation(sf::Texture *_texture, sf::Vector2u _imageCount, float _switchTime);
		~Animation();

		void update(int row, float dt, int stopAt, bool faceRight);

	public:
		sf::IntRect uvRect;

	private:
		sf::Vector2u imageCount;
		sf::Vector2u currentImage;

		float totalTime;
		float switchTime;
	};
};

