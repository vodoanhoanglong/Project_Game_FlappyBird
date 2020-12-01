#include "Collision.hpp"
#include <iostream>
namespace BTL
{
	Collision::Collision()
	{
	}

	Collision::~Collision()
	{
	}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2)
	{
		// Rect rect(left, top, width và height)
		sf::Rect<float> rect1 = sprite1.getGlobalBounds(); // khai báo rect1 = giới hạn của sprites1 gồm x và y
		sf::Rect<float> rect2 = sprite2.getGlobalBounds(); // khai báo rect2 = giới hạn của sprites2 gồm x và y

		if (rect1.intersects(rect2)) // nếu ((2 hình chồng lên nhau thì thì true, còn ngược lại false) == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Collision::CheckSpriteCollision(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2)
	{
		sprite1.setScale(scale1, scale1); // setScale đặt kết cấu có kích thước to hoặc nhỏ hơn
		sprite2.setScale(scale2, scale2);

		sf::Rect<float> rect1 = sprite1.getGlobalBounds(); // tương tự dòng 16
		sf::Rect<float> rect2 = sprite2.getGlobalBounds();

		if (rect1.intersects(rect2)) // nếu ((2 hình chồng lên nhau thì thì true, còn ngược lại false) == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}