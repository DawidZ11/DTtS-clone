#include "Game.h"

#include "MainMenuState.h"
#include <fstream>
#include <iostream>

int Game::m_gBestScore;
int Game::m_gGamesPlayed;
BirdSkin Game::m_gBirdSkin;

Game::Game(int _width, int _height, const std::string& _title)
{
	m_GameData->window.create(sf::VideoMode(_width, _height), "Don't touch the spikes", sf::Style::Close | sf::Style::Titlebar);

	std::fstream file;
	file.open("Data/data.txt", std::ios::in);

	if (file.is_open())
	{
		std::string line;

		std::getline(file, line);
		Game::m_gBestScore = atoi(line.c_str());

		std::getline(file, line);
		Game::m_gGamesPlayed = atoi(line.c_str());

		std::getline(file, line);
		Game::m_gBirdSkin = (BirdSkin)atoi(line.c_str());

		file.close();
	}

	m_GameData->stateManager.AddState(StateRef(new MainMenuState(m_GameData)));

	Run();
}

void Game::Run()
{
	float newTime, frameTime, interpolation;

	float currTime = m_Clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (m_GameData->window.isOpen())
	{
		newTime = m_Clock.getElapsedTime().asSeconds();
		frameTime = newTime - currTime;

		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currTime = newTime;
		accumulator += frameTime;

		while (accumulator >= m_dt)
		{
			m_GameData->stateManager.GetActiveState()->HandleInput();
			m_GameData->stateManager.GetActiveState()->Update(m_dt);

			accumulator -= m_dt;
		}

		interpolation = accumulator / m_dt;
		m_GameData->stateManager.GetActiveState()->Draw(interpolation);
	}
}
