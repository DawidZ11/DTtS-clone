#pragma once

#include <SFML/Graphics.hpp>

class Game
{
	sf::RenderWindow m_window;
	//State currstate

public:
	Game();
	~Game() {};

	bool Initialize(int _width, int _height);

	void Run();
};