#include "InputManager.h"

#include <iostream>

bool InputManager::IsSpriteClicked(sf::Sprite& _sprite, sf::Mouse::Button _button, sf::RenderWindow& _window)
{
	return sf::Mouse::isButtonPressed(_button) &&
		_sprite.getGlobalBounds().contains(sf::Vector2f(GetMousePosition(_window)));
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& _window)
{
	return sf::Mouse::getPosition(_window);
}
