#include "Animation.h"

#include <iostream>

namespace kaal 
{
	Animation::Animation(sf::Texture * _texture, sf::Vector2u _imageCount, float _switchTime) :
		imageCount(_imageCount),
		switchTime(_switchTime),
		totalTime(0.f),
		currentImage()
	{
		uvRect.width = _texture->getSize().x / _imageCount.x;
		uvRect.height = _texture->getSize().y / _imageCount.y;
	}

	Animation::~Animation()
	{

	}

	void Animation::update(int row, float dt, int stopAt, bool faceRight)
	{
		currentImage.y = row;
		totalTime += dt;

		if (totalTime >= switchTime)
		{
			totalTime -= switchTime;
			currentImage.x++;

			if (currentImage.x > stopAt)
			{
				currentImage.x = 0;
			}

			uvRect.top = currentImage.y * uvRect.height;

			if (faceRight)
			{
				uvRect.left = currentImage.x * std::abs(uvRect.width);
				uvRect.width = std::abs(uvRect.width);
			}
			else
			{
				uvRect.left = (currentImage.x + 1) * std::abs(uvRect.width);
				uvRect.width = -std::abs(uvRect.width);
			}
		}
	}
};
