#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace BTL
{
	class Pipe
	{
	public:
		Pipe(GameDataRef data);

		void SpawnBottomPipe();
		void SpawnTopPipe();
		void SpawnInvisiblePipe();
		void SpawnScoringPipe();
		void MovePipes(float dt);
		void DrawPipes();
		void RandomisePipeOffset();

		const std::vector<sf::Sprite> &GetSprites() const; // const ở đây là đối tượng chỉ xem k thể thay đổi giá trị
		std::vector<sf::Sprite> &GetScoringSprites(); // khai báo hàm có kiểu dữ liệu là sf::Sprite, hàm này là 1 vector

	private:
		GameDataRef _data;
		std::vector<sf::Sprite> pipeSprites; // khai báo biến là 1 vector có kiểu dữ liệu là sf::Sprite
		std::vector<sf::Sprite> scoringPipes; 

		int _landHeight;
		int _pipeSpawnYOffset;

	};
}