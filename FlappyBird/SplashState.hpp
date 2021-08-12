#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace BTL
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data); // hàm khởi tạo

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data; // khai báo _data là kiểu dữ liệu GameDataRef

		sf::Clock _clock; // khai báo đối tượng _clock trong lớp Clock

		sf::Sprite _background; // khai báo _background
	};
}