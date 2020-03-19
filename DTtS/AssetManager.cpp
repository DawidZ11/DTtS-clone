#include "AssetManager.h"

#include <iostream>

void AssetManager::LoadTexture(const std::string& _name, const std::string& _fileName)
{
	sf::Texture tex;

	if (tex.loadFromFile(_fileName))
		m_textures[_name] = tex;
}

sf::Texture& AssetManager::GetTexture(const std::string& _name)
{
	return m_textures.at(_name);
}

void AssetManager::LoadFont(const std::string& _name, const std::string& _fileName)
{
	sf::Font font;

	if (font.loadFromFile(_fileName))
		m_fonts[_name] = font;
}

sf::Font& AssetManager::GetFont(const std::string& _name)
{
	return m_fonts.at(_name);
}
