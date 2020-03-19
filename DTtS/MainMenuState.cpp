#include "MainMenuState.h"

#include <iostream>

#include "GameState.h"

MainMenuState::MainMenuState(GameDataRef _gameData)
	: m_GameData(_gameData)
{
	m_birdY = 0;
	m_birdVel = 88.0f;
}

void MainMenuState::Initialize()
{
	m_GameData->assets.LoadTexture("MainMenuBackground", "Resources/main_menu_background.png");
	m_GameData->assets.LoadTexture("BirdNormal", "Resources/bird.png");
	m_GameData->assets.LoadTexture("BirdUp", "Resources/bird_up1.png");

	m_GameData->assets.LoadFont("GlobalFont", "Resources/Blissful Thinking.otf");

	m_background.setTexture(m_GameData->assets.GetTexture("MainMenuBackground"));

	m_bird.setTexture(m_GameData->assets.GetTexture("BirdNormal"));
	m_bird.setOrigin(m_bird.getPosition().x + m_bird.getLocalBounds().width / 2.0f - 10.0f, m_bird.getPosition().y + m_bird.getLocalBounds().height / 2.0f - 12.0f);
	m_bird.setPosition(300.0f, 400.0f + m_birdY);

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

	m_Clock.restart();
}

void MainMenuState::HandleInput()
{
	sf::Event evnt;

	while (m_GameData->window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed)
			m_GameData->window.close();
	}
	if (m_Clock.getElapsedTime().asSeconds() > 0.3)
	{
		if (m_GameData->input.IsSpriteClicked(m_background, sf::Mouse::Left, m_GameData->window))
		{
			m_GameData->stateManager.AddState(StateRef(new GameState(m_GameData)));
		}
	}
}

void MainMenuState::Update(float _dt)
{
	m_birdY += m_birdVel * _dt;

	static bool texUp = false;

	if (abs(m_birdY) <= 0.5f)
	{
		if (texUp)
		{
			m_bird.setTexture(m_GameData->assets.GetTexture("BirdNormal"));
			texUp = false;
		}
		else
		{
			m_bird.setTexture(m_GameData->assets.GetTexture("BirdUp"));
			texUp = true;
		}
	}

	if (abs(m_birdY) >= 25.0f)
		m_birdVel = -m_birdVel;

	m_bird.setPosition(300.0f, 400.0f + m_birdY);
}

void MainMenuState::Draw(float _dt)
{
	m_GameData->window.clear();
	m_GameData->window.draw(m_background);
	m_GameData->window.draw(m_bird);

	m_GameData->window.draw(m_bestScore);
	m_GameData->window.draw(m_gamesPlayed);

	m_GameData->window.display();
}
