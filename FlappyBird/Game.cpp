#include "Game.hpp"
#include "SplashState.hpp"
#include <stdlib.h>
#include <time.h>


namespace BTL
{
	Game::Game(int width, int height, std::string title)
	{
		srand(time(NULL)); // time(NULL) trả về time hiện tại, còn srand thì cho ra số ngẫu nhiên dựa trên time hiện tại

		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar); // tạo kích thước cho cửa sổ, tiêu đề cho cửa sổ và phong cách của cửa sổ: có nút đóng và có thanh tiêu đề
		_data->machine.AddState(StateRef(new SplashState(this->_data))); // gọi hàm AddState trong đối tượng machine của lớp StateMachine
	    // sau đó gọi hàm khởi tạo của class StateRef, new SplashState ở đây là khi gọi hàm sẽ truyền vào 1 đối tượng và sẽ cấp phát bộ nhớ cho nó theo kiểu dữ liệu SplashState có _data ô nhớ 

		this->Run(); // gọi hàm Run
	}

	void Game::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds(); // gán currentTime = time tính bằng s 
		float accumulator = 0.0f; 

		while (this->_data->window.isOpen()) // nếu cửa sổ mở thì chạy CT
		{
			this->_data->machine.ProcessStateChanges(); // gọi hàm ProcessStateChanges trong StateMachine.cpp

			newTime = this->_clock.getElapsedTime().asSeconds(); // gán newTime = time tính bằng s 
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput(); // gọi hàm trong StateMachine.cpp r gọi tới State.cpp
				this->_data->machine.GetActiveState()->Update(dt);

				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation); // tương tự dòng 44
		}
	}
}
