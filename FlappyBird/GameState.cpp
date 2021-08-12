#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include "GameOverState.hpp"

#include <iostream>

namespace BTL
{
	GameState::GameState(GameDataRef data) : _data(data) // ds khởi tạo gán _data = data
	{

	}

	void GameState::Init()
	{
		if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH)) // nếu load lên fail 
		{
			std::cout << "Error Loading Hit Sound Effect" << std::endl;
		}

		if (!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH)) // nếu load lên fail 
		{
			std::cout << "Error Loading Wing Sound Effect" << std::endl;
		}

		if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH)) // nếu load lên fail 
		{
			std::cout << "Error Loading Point Sound Effect" << std::endl;
		}

		_hitSound.setBuffer(_hitSoundBuffer); // setBuffer là đặt đối tượng _hitSound có chứa dữ liệu âm thanh đã load lên ở trên
		_wingSound.setBuffer(_wingSoundBuffer); // tương tự
		_pointSound.setBuffer(_pointSoundBuffer); // tương tự
		
        // gọi hàm LoadTexture ở assets của class AssetManager gồm tên tự định nhĩa và hằng số chứa file để bỏ vào _data
		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH); 
		this->_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		this->_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		this->_data->assets.LoadTexture("Land", LAND_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
		this->_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		this->_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

		// cấp phát
		pipe = new Pipe(_data); 
		land = new Land(_data);
		bird = new Bird(_data);
		flash = new Flash(_data);
		hud = new HUD(_data);

		_background.setTexture(this->_data->assets.GetTexture("Game Background")); // _background.setTexture() đặt kết cấu hình ảnh bằng cách gọi hàm GetTexture(tên đã định nghĩa)

		_score = 0;
		hud->UpdateScore(_score); // gọi hàm cập nhật điểm để hiển thị số 0

		_gameState = GameStates::eReady; // gán _gameState = phạm vi:: eReady (trong DEFINITIONS.hpp)
	}

	void GameState::HandleInput()
	{
		sf::Event event; // khái báo đối tượng sự kiện

		while (this->_data->window.pollEvent(event)) // nhiều sự kiện có thể trong hàng đợi sự kiện nên khai báo vòng lặp để xử lý mọi sự kiện
		{
			if (sf::Event::Closed == event.type) // nếu sự kiện đóng cửa sổ = loại sự kiện đó trong EventType
			{
				this->_data->window.close(); // đóng cửa sổ
			}

			if (this->_data->input.IsSpriteClicked(this->_background, sf::Mouse::Left, this->_data->window)) // nếu trả về true thì tiếp, chi tiết trong InputManager.cpp
			{
				if (GameStates::eGameOver != _gameState) // nếu GameStates::eGameOver != _gameState thì tiếp tục mà lúc này _gameState = GameStates::eReady
				{
					_gameState = GameStates::ePlaying; // gán _gameState = GameStates::ePlaying
					bird->Tap(); // gọi hàm Tap()  trong Bird.cpp

					_wingSound.play(); // khi nhấn cho chim bay lên thì chạy âm thanh
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		if (GameStates::eGameOver != _gameState) // nếu GameStates::eGameOver != _gameState thì tiếp tục mà lúc này _gameState = GameStates::ePlaying 
		{
			bird->Animate(dt); // gọi đến hàm Animate trong class Bird.cpp và truyền đối tượng dt vào
			land->MoveLand(dt); // gọi đến hàm MoveLand trong class Land.cpp và truyền đối tượng dt vào
		}

		if (GameStates::ePlaying == _gameState) // nếu GameStates::ePlaying == _gameState thì tiếp tục mà lúc này _gameState = GameStates::ePlaying 
		{
			pipe->MovePipes(dt); // gọi hàm đến MovePipes trong class Pipe.cpp

			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY) // nếu đối tượng clock lấy ra time tính = s mà > 1.5f
			{
				pipe->RandomisePipeOffset(); // gọi hàm đến RandomisePipeOffset trong class Pipe.cpp

				pipe->SpawnInvisiblePipe(); // tương tự
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();
				pipe->SpawnScoringPipe();

				clock.restart(); // restart lại time về 0s
			}

			bird->Update(dt); // gọi hàm Update trong Bird.cpp

			std::vector<sf::Sprite> landSprites = land->GetSprites(); // khai báo vector landSprites kiểu dữ liệu tự định nghĩa sf::Sprite = gọi hàm GetSprites trong Land.cpp

			for (int i = 0; i < landSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.7f, landSprites.at(i), 1.0f)) // nếu hàm CheckSpriteCollision trả về true thì tiếp tục, chi tiết ở Collision.cpp
				{
					_gameState = GameStates::eGameOver; // gán _gameState = GameStates::eGameOver

					clock.restart(); // restart về time = 0s

					_hitSound.play(); // khi va chạm mặt đất sẽ phát âm thanh
				}
			}

			std::vector<sf::Sprite> pipeSprites = pipe->GetSprites(); // khai báo 1 vector pipeSprites kiểu dữ liệu sf::Sprite = gọi hàm GetSprites trong Pipe.cpp

			for (int i = 0; i < pipeSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeSprites.at(i), 1.0f)) // tương tự dòng 119
				{
					_gameState = GameStates::eGameOver; // tương tự

					clock.restart(); // tương tự

					_hitSound.play(); // khai va chạm ống sẽ phát âm thanh
				}
			}

			if (GameStates::ePlaying == _gameState) // nếu _gameState chưa bị gán = eGameOver thì tiếp tục
			{
				std::vector<sf::Sprite> &scoringSprites = pipe->GetScoringSprites(); // khai báo vector có tham chiếu vì điểm thay đổi khi qua mỗi ống = gọi hàm GetScoringSprites

				for (int i = 0; i < scoringSprites.size(); i++)
				{
					if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites.at(i), 1.0f)) // nếu chim va chạm khoảng trống thì tiếp tục
					{
						_score++; // _score =  _score + 1

						hud->UpdateScore(_score); // gọi đến hàm UpdateScore trong HUD.cpp để in điểm lên

						scoringSprites.erase(scoringSprites.begin() + i); // xóa ptu thứ 0 + i trong scoringSprites

						_pointSound.play(); // khi va chạm khoảng trống thì phát âm thanh
					}
				}
			}
		}

		if (GameStates::eGameOver == _gameState) // nếu _gameState bị gán = eGameOver thì tiếp tục
		{
			flash->Show(dt); // gọi đến hàm Show trong flash.cpp

			if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS) // nếu time(s) > 1.5f
			{
				this->_data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);// gọi hàm AddState trong đối tượng machine của lớp StateMachine
			    // sau đó gọi hàm khởi tạo của class StateRef, new GameOverState ở đây là khi gọi hàm sẽ truyền vào 1 đối tượng và sẽ cấp phát bộ nhớ cho nó theo kiểu dữ liệu là GameOverState
				// 1 cái sẽ nằm trong giới hạn của_data và 1 cái trong giới hạn _score, tức là cấp phát cho 1 đối tượng 2 lần có cùng kiểu dữ liệu, khác giới hạn ô nhớ
			}
		}
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red); // xóa toàn bộ màu đỏ trên cửa sổ

		this->_data->window.draw(this->_background); // vẽ _background lên

		pipe->DrawPipes(); // gọi đến hàm DrawPipes trong Pipe.cpp
		land->DrawLand(); // gọi hàm DrawLand trong Land.cpp
		bird->Draw(); // gọi hàm Draw trong Bird.cpp

		flash->Draw(); // gọi hàm Draw trong flash.cpp  

		hud->Draw(); // gọi hàm Draw trong HUD.cpp

		this->_data->window.display(); // hiển thị trên màn hình những gì đã được hiển thị trong cửa sổ cho đến nay.
	}
}