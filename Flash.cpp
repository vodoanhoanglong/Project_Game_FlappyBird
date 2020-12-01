#include "Flash.hpp"

namespace BTL
{
	Flash::Flash(GameDataRef data) : _data(data) // ds khởi tạo gán _data = data
	{
		_shape = sf::RectangleShape(sf::Vector2f(_data->window.getSize().x, _data->window.getSize().y)); // gán _shape = kích thước width và kích thước height
		_shape.setFillColor(sf::Color(255, 255, 255, 0)); // đặt đối tượng _shape có màu red, green, blue, alpha(độ mờ), độ mờ càng nhỏ thì càng mờ

		_flashOn = true;
	}

	Flash::~Flash()
	{
	}

	void Flash::Show(float dt)
	{
		if (_flashOn)
		{
			int alpha = (int)_shape.getFillColor().a + (FLASH_SPEED * dt); // gán alpha = mã màu + 1500.0f * dt

			if (alpha >= 255.0f) 
			{
				alpha = 255.0f;
				_flashOn = false;
			}

			_shape.setFillColor(sf::Color(255, 255, 255, alpha)); // alpha lúc này = 255.0f
		}
		else
		{
			int alpha = (int)_shape.getFillColor().a - (FLASH_SPEED * dt); // gán alpha = mã màu - 1500.0f * dt

			if (alpha <= 0.0f)
			{
				alpha = 0.0f;
			}

			_shape.setFillColor(sf::Color(255, 255, 255, alpha)); // alpha lúc này = 0.0f
		}
	}

	void Flash::Draw()
	{
		_data->window.draw(_shape); // vẽ đối tượng _shape lên
	}
}