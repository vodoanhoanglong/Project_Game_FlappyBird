#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"

namespace BTL
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data); // hàm khởi tạo

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background; // khai báo đối tượng _background trong class sf::Sprite

		Pipe *pipe;
		Land *land;
		Bird *bird;
		Collision collision;
		Flash *flash;
		HUD *hud;

		sf::Clock clock; // khai báo đối tượng clock trong class sf::Clock

		int _gameState;

		sf::RectangleShape _gameOverFlash; // khai báo đối tượng _gameOverFlash trong class sf::RectangleShape
		bool _flashOn;

		int _score;

		sf::SoundBuffer _hitSoundBuffer; // khai báo tương tự
		sf::SoundBuffer _wingSoundBuffer;
		sf::SoundBuffer _pointSoundBuffer;

		sf::Sound _hitSound;
		sf::Sound _wingSound;
		sf::Sound _pointSound;

	};
}