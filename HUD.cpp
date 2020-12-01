#include "HUD.hpp"

#include <string>

namespace BTL
{
	HUD::HUD(GameDataRef data) : _data(data)
	{
		_scoreText.setFont(this->_data->assets.GetFont("Flappy Font"));  // đặt font chữ cho đối tượng _scoreText bằng cách gọi hàm GetFont() theo tên đã định nghĩa

		_scoreText.setString("0"); // đặt _scoreText là chuỗi ký tự, ban đầu là "0"

		_scoreText.setCharacterSize(128); // đặt kích thước ký tự là 128

		_scoreText.setFillColor(sf::Color::White); // đặt màu cho ký tự là màu trắng

		_scoreText.setOrigin(sf::Vector2f(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2)); // setOrigin thiết lập nguồn gốc cục bộ của đối tượng
		// Vector2f là 1 vector có chứa 2 dữ liệu kiểu float(max width / 2, max height / 2)
		_scoreText.setPosition(sf::Vector2f(_data->window.getSize().x / 2, _data->window.getSize().y / 5)); // setPosition là đặt vị trí cho đối tượng
		// Vector2f là 1 vector có chứa 2 dữ liệu kiểu float(kích thước độ rộng của cửa sổ / 2, kích thước độ cao của cửa sổ / 5)
	}

	HUD::~HUD()
	{
	}

	void HUD::Draw()
	{
		_data->window.draw(_scoreText); // vẽ đối tượng lên
	}

	void HUD::UpdateScore(int score)
	{
		_scoreText.setString(std::to_string(score)); // cập nhật ký tự cũ thành ký tự mới thông qua biến score
	}
}