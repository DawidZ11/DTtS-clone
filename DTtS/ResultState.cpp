#include "ResultState.h"

#include "MainMenuState.h"
#include <iostream>

ResultState::ResultState(GameDataRef _gameData, int _finalScore)
	: m_GameData(_gameData), m_finalScoreCount(_finalScore)
{
	std::cout << m_finalScoreCount;
}

void ResultState::Initialize()
{
	m_GameData->assets.LoadTexture("Result", "Resources/result.png");
	m_GameData->assets.LoadTexture("ReplayButton", "Resources/replay_button.png");

	m_background.setTexture(m_GameData->assets.GetTexture("MainMenuBackground"));

	m_bestScore.setFont(m_GameData->assets.GetFont("GlobalFont"));
	m_bestScore.setCharacterSize(42);
	m_bestScore.setFillColor(sf::Color(140, 140, 140, 255));
	m_bestScore.setString(std::to_string(Game::m_gBestScore));
	m_bestScore.setPosition(396.0f, 649.0f);

	m_gamesPlayed.setFont(m_GameData->assets.GetFont("GlobalFont"));
	m_gamesPlayed.setCharacterSize(42);
	m_gamesPlayed.setFillColor(sf::Color(140, 140, 140, 255));
	m_gamesPlayed.setString(std::to_string(Game::m_gGamesPlayed));
	m_gamesPlayed.setPosition(426.0f, 690.0f);

	m_result.setTexture(m_GameData->assets.GetTexture("Result"));
	m_result.setOrigin(m_result.getGlobalBounds().width / 2.0f, m_result.getGlobalBounds().height / 2.0f);
	m_result.setPosition(300.0f, 330.0f);

	m_finalScore.setFont(m_GameData->assets.GetFont("GlobalFont"));
	m_finalScore.setCharacterSize(50);
	m_finalScore.setFillColor(sf::Color::White);
	m_finalScore.setString(std::to_string(m_finalScoreCount));
	m_finalScore.setOrigin(m_finalScore.getGlobalBounds().width / 2.0f, m_finalScore.getGlobalBounds().height / 2.0f);
	m_finalScore.setPosition(300.0f, 300.0f);

	m_replay.setTexture(m_GameData->assets.GetTexture("ReplayButton"));
	m_replay.setOrigin(m_replay.getGlobalBounds().width / 2.0f, m_replay.getGlobalBounds().height / 2.0f);
	m_replay.setPosition(300.0f, 465.0f);

	m_Clock.restart();
}

void ResultState::HandleInput()
{
	sf::Event evnt;

	while (m_GameData->window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed)
			m_GameData->window.close();
	}

	if (m_Clock.getElapsedTime().asSeconds() > 0.4)
	{
		if (m_GameData->input.IsSpriteClicked(m_replay, sf::Mouse::Left, m_GameData->window))
		{
			m_GameData->stateManager.AddState(StateRef(new MainMenuState(m_GameData)));
		}
	}
}

void ResultState::Update(float _dt)
{
}

void ResultState::Draw(float _dt)
{
	m_GameData->window.clear();

	m_GameData->window.draw(m_background);
	m_GameData->window.draw(m_replay);
	m_GameData->window.draw(m_result);
	m_GameData->window.draw(m_finalScore);

	m_GameData->window.draw(m_bestScore);
	m_GameData->window.draw(m_gamesPlayed);

	m_GameData->window.display();
}
