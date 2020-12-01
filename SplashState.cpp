#pragma once

#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace BTL
{
	SplashState::SplashState(GameDataRef data) : _data(data) // ds khởi tạo gán _data = data
	{

	}

	void SplashState::Init()
	{
		this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH); // gọi hàm LoadTexture đặt tên theo vị trí ptu, và 1 hằng chứa file

		_background.setTexture(this->_data->assets.GetTexture("Splash State Background")); // đặt _background có kết cấu là: ptu có tên Splash State Background trong hàm GetTexture
	}

	void SplashState::HandleInput()
	{
		sf::Event event; // khai báo biến sự kiện

		while (this->_data->window.pollEvent(event)) // nhiều sự kiện có thể trong hàng đợi sự kiện nên khai báo vòng lặp để xử lý mọi sự kiện
		{
			if (sf::Event::Closed == event.type) // sự kiện đóng cửa sổ = loại sự kiện đó trong EventType
			{
				this->_data->window.close(); // đóng cửa sổ
			}
		}
	}

	void SplashState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) // nếu time (s) > 0.0
		{
			// Chuyển sang Menu chính
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true); // gọi hàm AddState trong đối tượng machine của lớp StateMachine
			// sau đó gọi hàm khởi tạo của class StateRef, new MainMenuState ở đây là khi gọi hàm sẽ truyền vào 1 đối tượng và sẽ cấp phát bộ nhớ cho nó theo kiểu dữ liệu MainMenuState có _data ô nhớ
		}
	}

	void SplashState::Draw(float dt)
	{
		this->_data->window.clear(); // xóa toàn bộ đối tượng với một màu 

		this->_data->window.draw( this->_background ); // vẽ đối tượng _background lên 
	
		this->_data->window.display(); // hiển thị trên màn hình những gì đã được hiển thị trong cửa sổ cho đến nay.
	}
}