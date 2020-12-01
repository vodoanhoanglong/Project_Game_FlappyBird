#include "Land.hpp"
#include "DEFINITIONS.hpp"

namespace BTL
{
	Land::Land(GameDataRef data) : _data(data) // ds khởi tạo gán _data = data
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Land")); // gọi hàm GetTexture lấy hình đã load lên
		sf::Sprite sprite2(this->_data->assets.GetTexture("Land")); // tương tự

		sprite.setPosition(0, this->_data->window.getSize().y - sprite.getLocalBounds().height); // đặt vị trí: x: 0, y: kích thước chiều cao của cửa sổ - chiều cao tối đa của sprite
		sprite2.setPosition(sprite.getLocalBounds().width, this->_data->window.getSize().y - sprite2.getLocalBounds().height); 
		// đặt vị trí: x: chiều rộng tối đa của sprite, x: chiều cao của cửa sổ - chiều cao tối đa của sprite2
		_landSprites.push_back(sprite); // đưa sprite vào _landSprites
		_landSprites.push_back(sprite2); // đưa sprite2 vào _landSprites
	}

	void Land::MoveLand(float dt)
	{
		for (unsigned short int i = 0; i < _landSprites.size(); i++)  // unsigned short int: 0 đến 65,535
		{
			sf::Vector2f position = _landSprites.at(i).getPosition(); // khai báo position là kiểu vector chứa đc 2 dữ liệu float, gán position = lấy ra vị trí của ptu thứ i gồm tọa độ x, y
			float movement = PIPE_MOVEMENT_SPEED * dt; // khai báo movement = 200.0f * dt

			_landSprites.at(i).move(-movement, 0.0f); // di chuyển vị trí của _landSprites thứ i từ vị trí đã đc đặt thành: tọa độ x bây giờ = -movement, tọa độ y = 0.0f

			if (_landSprites.at(i).getPosition().x < 0 - _landSprites.at(i).getLocalBounds().width) // nếu vị trí tọa độ x trong ptu thứ i < 0 - chiều rộng tối đa của ptu thứ i 
			{
				sf::Vector2f position(_data->window.getSize().x, _landSprites.at(i).getPosition().y); // khai báo position là kiểu vector chứa đc 2 dữ liệu float
				// tọa độ x: lấy kích thước width của cửa sổ, tọa độ y: lấy vị trí y của ptu thứ i 
				_landSprites.at(i).setPosition(position); // đặt vị trí của ptu thứ i theo vị trí position dòng trên
			}
		}
	}

	void Land::DrawLand()
	{
		for (unsigned short int i = 0; i < _landSprites.size(); i++) // tương tự dòng 20
		{
			this->_data->window.draw(_landSprites.at(i)); // vẽ lên cửa sổ ptu thứ i
		}
	}

	const std::vector<sf::Sprite> &Land::GetSprites() const
	{
		return _landSprites;
	}
}