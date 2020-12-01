#pragma once

#include "InputManager.hpp"

namespace BTL
{
	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(button)) // kiểm tra xem nút chuột có đc nhấn k, nếu nhấn đc thì = true
		{
			sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
			// IntRect ...(left, top, width, heigh)
			// playButtonRect(lấy vị trí chiều rộng của obj, lấy vị trí chiều cao của obj, lấy ra giới hạn độ rộng của obj, lấy ra giới hạn độ cao của obj)
			if (playButtonRect.contains(sf::Mouse::getPosition(window))) // KT xem vị trí của chuột trong cửa sổ có nằm trong vị trí playButtonRect hay k, nếu nằm trong thì trả về true
			{
				return true;
			}
		}

		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window) // vector 2 chiều có kiểu dữ liệu là int
	{
		return sf::Mouse::getPosition(window); // trả về vị trí của chuột trong cửa sổ
	}
}