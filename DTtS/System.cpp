#include "Game.h"

Game::Game()
{ }

bool Game::Initialize(int _width, int _height)
{
	m_window.create(sf::VideoMode(_width, _height), "Don't touch the spikes");
	m_window.setVerticalSyncEnabled(true);

	return true;
}

void Game::Run()
{
	sf::Event evnt;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				m_window.close();
		}

		//state.update
		//state.render
		m_window.clear();
		m_window.display();
	}
}
