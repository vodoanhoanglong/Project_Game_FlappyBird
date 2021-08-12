#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace BTL
{
	class Land
	{
	public:
		Land(GameDataRef data); // khởi tạo

		void MoveLand(float dt);
		void DrawLand();

		const std::vector<sf::Sprite> &GetSprites() const; // k thể thay đổi giá trị

	private:
		GameDataRef _data;

		std::vector<sf::Sprite>_landSprites;

	};
}