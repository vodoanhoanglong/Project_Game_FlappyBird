#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"

#include <iostream>

namespace BTL
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH); // gọi đến hàm LoadTexture đã đc cài đặt, Main Menu Background là tên ptu, MAIN_MENU_BACKGROUND_FILEPATH là tên đc định nghĩa dẫn tới file chứa hình
		this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH); // tương tự dòng 19
		this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH); // tương tụ dòng 19

		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background")); // thay đổi kết cấu của hình lấy ra bằng hàm GetTexture()
		_title.setTexture(this->_data->assets.GetTexture("Game Title")); // tương tự dòng 23
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button")); // tương tự dòng 23

		_title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2); // đặt vị trí cho _title là (768 / 2) - (giới hạn độ rộng / 2), (giới hạn độ cao / 2)
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2)); // đặt vị trí cho _playButton là (768 / 2) - (giới hạn độ rộng / 2), (1024 / 2) - (giới hạn độ cao / 2)
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event; // khai báo sự kiện

		while (this->_data->window.pollEvent(event)) // nhiều sự kiện có thể trong hàng đợi sự kiện nên khai báo vòng lặp để xử lý mọi sự kiện
		{
			if (sf::Event::Closed == event.type) // nếu sự kiện đóng cửa sổ = loại sự kiện đó trong EventType
			{
				this->_data->window.close(); // đóng cửa sổ
			}

			if (this->_data->input.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window)) // gọi đến hàm IsSpriteClicked nếu click trong khung _playButton bằng chuột trái thì true
			{
				// chuyển sang Menu chính
				this->_data->machine.AddState(StateRef(new GameState(_data)), true); // gọi hàm AddState trong đối tượng machine của lớp StateMachine
			    // sau đó gọi hàm khởi tạo của class StateRef, new GameState ở đây là khi gọi hàm sẽ truyền vào 1 đối tượng và sẽ cấp phát bộ nhớ cho nó theo kiểu dữ liệu GameState có _data ô nhớ 
			}
		}
	}

	void MainMenuState::Update(float dt)
	{
		
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(); // xóa toàn bộ đối tượng với một màu: đỏ 

		this->_data->window.draw(this->_background); // vẽ đối tượng _background lên mục tiêu
		this->_data->window.draw(this->_title); // vẽ đối tượng _title lên mục tiêu
		this->_data->window.draw(this->_playButton); // vẽ đối tượng _playButton lên mục tiêu

		this->_data->window.display(); // hiển thị trên màn hình những gì đã được hiển thị trong cửa sổ cho đến nay.
	}
}