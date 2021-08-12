#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace BTL
{
	class HUD
	{
	public:
		HUD(GameDataRef data); // hàm khởi tạo
		~HUD();

		void Draw();
		void UpdateScore(int score);

	private:
		GameDataRef _data;

		sf::Text _scoreText; // khai báo đối tượng _scoreText trong class sf::Text

	};
}