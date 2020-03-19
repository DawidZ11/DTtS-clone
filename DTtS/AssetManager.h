#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager
{
	std::map<std::string, sf::Texture>	m_textures;
	std::map<std::string, sf::Font>		m_fonts;

public:
	void LoadTexture(const std::string& _name, const std::string& _fileName);
	sf::Texture& GetTexture(const std::string& _name);

	void LoadFont(const std::string& _name, const std::string& _fileName);
	sf::Font& GetFont(const std::string& _name);
};

