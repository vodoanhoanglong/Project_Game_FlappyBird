#include "Bird.hpp"

namespace BTL
{
	Bird::Bird(GameDataRef data) : _data(data) // ds khởi tạo gán _data = data
	{
		_animationIterator = 0;

		_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 1")); // GetTexture(std::string name) là hàm tự định nghĩa
		_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 2"));
		_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 3"));
		_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 4"));

		_birdSprite.setTexture(_animationFrames.at(_animationIterator)); // thay đổi kết cấu từ phần tử 0 trong vector
		
		_birdSprite.setPosition((_data->window.getSize().x / 4) - (_birdSprite.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_birdSprite.getGlobalBounds().height / 2));
	    // đặt vị trí cho Bird thứ 0 (chiều rộng / 4 - giới hạn độ rộng / 2 , chiều cao / 2 - giới hạn độ cao / 2)
		_birdState = BIRD_STATE_STILL; // 1
		// _birdState = 1
		sf::Vector2f origin = sf::Vector2f(_birdSprite.getGlobalBounds().width / 2, _birdSprite.getGlobalBounds().height / 2);
		// khai báo 1 vector chứa 2 dữ liệu float, 1f chứa giới hạn độ rộng / 2 còn lại chứa giới hạn độ cao / 2
		_birdSprite.setOrigin(origin);
		// điểm gốc của đối tượng là tọa độ liên quan đến góc trên bên trái của đối tượng, mặc định ban đầu (0, 0), ở đây thì origin đã chứa 2 dữ liệu ở dòng 20
		_rotation = 0;
	}

	Bird::~Bird()
	{
	}

	void Bird::Draw()
	{
		_data->window.draw(_birdSprite);
		// vẽ đối tượng Bird 
	}

	void Bird::Animate(float dt)
	{
		if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size()) // nếu time tính bằng s > 0.4f / 4
		{
			if (_animationIterator < _animationFrames.size() - 1) // 0 < 3
			{
				_animationIterator++; // tăng 1
			}
			else
			{
				_animationIterator = 0;
			}

			_birdSprite.setTexture(_animationFrames.at(_animationIterator)); // thay đổi kết cấu từ ptu 0->1

			_clock.restart(); // đặt time trở về = 0s
		}
	}

	void Bird::Update(float dt)
	{
		if (BIRD_STATE_FALLING == _birdState) // 2, 1
		{
			_birdSprite.move(0, GRAVITY * dt); // di chuyển bird từ vị trí đã đc đặt sau đó di chuyển tọa độ x thêm 0, di chuyển tọa độ y thêm 350.0f * dt

			_rotation += ROTATION_SPEED * dt; // _rotation = 0 + (100.0f * dt)

			if (_rotation > 25.0f)
			{
				_rotation = 25.0f;
			}

			_birdSprite.setRotation(_rotation); // thiết lập hướng của đối tượng
		}
		else if (BIRD_STATE_FLYING == _birdState) // 3, 1
		{
			_birdSprite.move(0, -FLYING_SPEED * dt); // di chuyển bird từ 0 + (-350.0f * dt)

			_rotation -= ROTATION_SPEED * dt; // _rotation = 0 - (100.0f * dt)

			if (_rotation < -25.0f)
			{
				_rotation = -25.0f;
			}

			_birdSprite.setRotation(_rotation);
		}

		if (_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION) // nếu 0s trở đi > 0.25f
		{
			_movementClock.restart(); // đặt lại 0s
			_birdState = BIRD_STATE_FALLING; // _birdState = 2
		}
	}

	void Bird::Tap()
	{
		_movementClock.restart();  // đặt lại 0s
		_birdState = BIRD_STATE_FLYING; // _birdState = 3
	}

	const sf::Sprite& Bird::GetSprite() const // tránh sao chép và ng gọi k thể thay đổi đối tượng
	{
		return _birdSprite;
	}
}