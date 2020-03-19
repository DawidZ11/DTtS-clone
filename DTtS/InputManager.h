#pragma once

#include <SFML/Graphics.hpp>

class InputManager
{

public:
	bool IsSpriteClicked(sf::Sprite& _sprite, sf::Mouse::Button _button, sf::RenderWindow& _window);
	
	sf::Vector2i GetMousePosition(sf::RenderWindow& _window);
};

