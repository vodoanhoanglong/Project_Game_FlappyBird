#include "Pipe.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace BTL
{
	Pipe::Pipe(GameDataRef data) : _data(data) // ds khởi tạo gán _data = data
	{
		_landHeight = this->_data->assets.GetTexture("Land").getSize().y; // gán _landHeight = gọi hàm GetTexture để lấy cái kích thước theo chiều cao của hình đã load lên theo tên đã định nghĩa 
		_pipeSpawnYOffset = 0;
	}

	void Pipe::SpawnBottomPipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Up"));
		// gọi hàm GetTexture lấy hình đã load lên theo tên
		sprite.setPosition(this->_data->window.getSize().x, this->_data->window.getSize().y - sprite.getLocalBounds().height - _pipeSpawnYOffset);
		// đặt vị trí nó ở: tọa độ x: lấy kích thước chiều rộng của cửa sổ, tọa độ y: lấy kích thước chiều cao của cửa sổ - giới hạn chiều cao của đối tượng sprite - 0
		pipeSprites.push_back(sprite); // đưa sprite vào pipeSprites
	}

	void Pipe::SpawnTopPipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Down")); // gọi hàm GetTexture để lấy hình trong mảng theo tên ptu là Pipe Down

		sprite.setPosition(this->_data->window.getSize().x, -_pipeSpawnYOffset/2); // đặt vị trí đối tượng ở: tọa độ x: kích thước theo chiều rộng của cửa sổ, tọa độ y: -0

		pipeSprites.push_back(sprite); // đưa sprite vào pipeSprites
	}

	void Pipe::SpawnInvisiblePipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Down")); // gọi hàm GetTexture lấy hình đã load lên theo tên

		sprite.setPosition(this->_data->window.getSize().x, -_pipeSpawnYOffset/2); // đặt vị trí đối tượng ở: tọa độ x: kích thước width của cửa sổ, tọa độ y: -0
		sprite.setColor(sf::Color(0, 0, 0, 0)); // đặt màu kết cấu thành k màu -> vô hình

		pipeSprites.push_back(sprite); // đưa sprite vào pipeSprites
	}

	void Pipe::SpawnScoringPipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Scoring Pipe")); // gọi hàm GetTexture lấy hình đã load lên theo tên

		sprite.setPosition(this->_data->window.getSize().x, 0); // đặt vị trí đối tượng: tọa độ x: lấy kích thước width của cửa sổ, tọa độ y: 0

		scoringPipes.push_back(sprite); // đưa sprite vào scoringPipes
	}

	void Pipe::MovePipes(float dt)
	{
		for ( int i = 0; i < pipeSprites.size(); i++)
		{
			if (pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getLocalBounds().width) // nếu vị trí tọa độ x của ptu thứ i < 0 - lấy vị trí của ptu i có độ rộng tối đa
			{
				pipeSprites.erase( pipeSprites.begin( ) + i ); // xóa ptu thứ 0 + i
			}
			else
			{
				sf::Vector2f position = pipeSprites.at(i).getPosition(); // khai báo position là kiểu vector chứa đc 2 dữ liệu float, gán position = lấy ra vị trí của ptu thứ i gồm tọa độ x, y
				float movement = PIPE_MOVEMENT_SPEED * dt; // khai báo movement = 200.0f * dt

				pipeSprites.at(i).move(-movement, 0); // di chuyển vị trí của pipeSprites thứ i từ vị trí đã đc đặt thành: tọa độ x bây giờ = -movement, tọa độ y = 0
			}
		}

		for (int i = 0; i < scoringPipes.size(); i++)
		{
			if (scoringPipes.at(i).getPosition().x < 0 - scoringPipes.at(i).getLocalBounds().width) // nếu vị trí tại tọa độ x của ptu thứ i trong scoringPipes < 0 - độ rộng tối đa của ptu thứ i trong scoringPipes
			{
				scoringPipes.erase(scoringPipes.begin() + i); // xóa ptu thứ 0 + i
			}
			else
			{
				sf::Vector2f position = scoringPipes.at(i).getPosition(); // khai báo position là kiểu vector chứa đc 2 dữ liệu float, gán position = lấy ra vị trí của ptu thứ i gồm tọa độ x, y
				float movement = PIPE_MOVEMENT_SPEED * dt; // khai báo movement = 200.0f * dt

				scoringPipes.at(i).move(-movement, 0); // di chuyển vị trí của scoringPipes thứ i từ vị trí đã đc đặt thành: tọa độ x bây giờ = -movement, tọa độ y = 0
			}
		}
	}

	void Pipe::DrawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++) // unsigned short int: 0 đến 65,535
		{
			this->_data->window.draw(pipeSprites.at(i)); // vẽ ptu thứ i của đối tượng pipeSprites
		}
	}

	void Pipe::RandomisePipeOffset()
	{
		_pipeSpawnYOffset = rand() % (_landHeight + 1); // _pipeSpawnYOffset = hàm cho ra số ngẫu nhiên chia lấy dư cho _landHeight + 1
	}

	const std::vector<sf::Sprite> &Pipe::GetSprites() const
	{
		return pipeSprites; 
	}

	std::vector<sf::Sprite> &Pipe::GetScoringSprites()
	{
		return scoringPipes;
	}
}