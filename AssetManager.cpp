#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

namespace BTL
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName)) // nếu load hình lên từ file thành công thì true
		{
			this->_textures[name] = tex; // gán cái _textures[tên tự định nghĩa] = hình vừa load
		}
	}

	sf::Texture &AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name); // lấy cái hình đã load lên theo tên đã định nghĩa
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

	sf::Font &AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}
}