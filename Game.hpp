#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

namespace BTL
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};
	//Sử dụng shared_ptr nếu bạn muốn chia sẻ quyền sở hữu tài nguyên.Nhiều shared_ptr có thể trỏ đến một tài nguyên.
	//shared_ptr duy trì số lượng tham chiếu cho đề xuất này.khi tất cả các trỏ tới tài nguyên của shared_ptr đi ra ngoài phạm vi, tài nguyên sẽ bị phá hủy.
	typedef std::shared_ptr<GameData> GameDataRef; // định nghĩa class std::shared_ptr<GameData> thành GameDataRef

	class Game
	{
	public:
		Game(int width, int height, std::string title);
	private:
		// Cập nhật chạy với tốc độ 60 mỗi giây
		const float dt = 1.0f / 60.0f; // hằng số chỉ đc thay đổi ở đây nếu gán dt = gì đó ở dưới thì lỗi
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>(); // khởi tạo 1 con trỏ thông minh _data có thể chia sẽ quyền sở hữu cho 1 con trỏ khác
		
		void Run();
	};
}