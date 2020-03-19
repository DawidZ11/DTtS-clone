#include "GameState.h"

#include "ResultState.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

GameState::GameState(GameDataRef _gameData)
	:m_GameData(_gameData)
{}

void GameState::Initialize()
{
	m_spikes1.clear();
	m_spikes2.clear();

	m_GameData->assets.LoadTexture("BirdUpOpen", "Resources/bird_up2.png");

	m_GameData->assets.LoadTexture("BirdNormalLeft", "Resources/bird-left.png");
	m_GameData->assets.LoadTexture("BirdUpOpenLeft", "Resources/bird_up2-left.png");

	m_GameData->assets.LoadTexture("SpikeLeft", "Resources/spike-left.png");
	m_GameData->assets.LoadTexture("SpikeRight", "Resources/spike-right.png");

	m_GameData->assets.LoadTexture("GameBackground", "Resources/game_background.png");

	m_spikesCount = 1;
	m_scoreCount = 0;

	m_scoreString = "0" + std::to_string(m_scoreCount);

	m_background.setTexture(m_GameData->assets.GetTexture("GameBackground"));

	m_score.setFont(m_GameData->assets.GetFont("GlobalFont"));
	m_score.setString(m_scoreString);
	m_score.setFillColor(sf::Color(235, 235, 235));
	m_score.setCharacterSize(230.0f);
	m_score.setOrigin(m_score.getLocalBounds().width / 2.0f, m_score.getLocalBounds().height / 2.0f);
	m_score.setPosition(307.0f, 330.0f);

	m_birdDir = BirdDir::BD_RIGHT;
	m_birdVel = sf::Vector2f(300.0f, -550.0f);

	m_bird.setTexture(m_GameData->assets.GetTexture("BirdNormal"));
	m_bird.setOrigin(m_bird.getLocalBounds().width / 2.0f, m_bird.getLocalBounds().height / 2.0f);
	m_bird.setPosition(300.0f, 400.0f);

	for (int i = 0; i < 5; i++)
		m_spikesPos[i] = 0;

	srand(time(NULL));
	m_spikesPos[0] = (rand() % 11) + 1;

	sf::Sprite tempSpike;
	tempSpike.setTexture(m_GameData->assets.GetTexture("SpikeRight"));
	tempSpike.setOrigin(tempSpike.getLocalBounds().width, 0.0f);
	//tempSpike.setPosition(540.0f, 30.0f + (m_spikesPos[0] * 67.0f) - 67.0f);
	tempSpike.setPosition(580.0f, 30.0f + (m_spikesPos[0] * 67.0f) - 67.0f);

	Game::m_gGamesPlayed++;

	m_spikes2.push_back(tempSpike);
}

GameState::~GameState()
{
}

void GameState::HandleInput()
{
	sf::Event evnt;

	while (m_GameData->window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed)
			m_GameData->window.close();
		else if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left)
		{
			if (m_birdDir == BD_LEFT)
				m_bird.setTexture(m_GameData->assets.GetTexture("BirdUpOpenLeft"));
			else
				m_bird.setTexture(m_GameData->assets.GetTexture("BirdUpOpen"));

			m_Clock.restart();

			m_birdVel.y = -550.0f;
		}
	}
}

void GameState::Update(float _dt)
{
	if (m_Clock.getElapsedTime().asSeconds() > 0.2)
	{
		if (m_birdDir == BD_LEFT)
			m_bird.setTexture(m_GameData->assets.GetTexture("BirdNormalLeft"));
		else
			m_bird.setTexture(m_GameData->assets.GetTexture("BirdNormal"));
	}

	static bool hide1 = false, hide2 = false;
	static bool adding1 = false, adding2 = false;

	sf::Vector2f pos = m_bird.getPosition();

	float g = 1500.0f;

	m_birdVel.y += g * _dt;

	m_bird.setPosition(pos.x + m_birdVel.x * _dt, pos.y + m_birdVel.y * _dt);

	if (CheckColisions())
		return;

	if (m_bird.getPosition().x > 530.0f)
	{
		AddScore();

		if (m_scoreCount >= 20)
			m_birdVel.x += 15.0f;

		m_birdDir = BD_LEFT;
		m_birdVel.x = -m_birdVel.x;
		m_bird.setTexture(m_GameData->assets.GetTexture("BirdNormalLeft"));


		hide2 = true;
		adding1 = true;

	}
	else if(m_bird.getPosition().x < 70.0f)
	{
		AddScore();

		if (m_spikesCount >= 20)
			m_birdVel.x -= 15.0f;

		m_birdDir = BD_RIGHT;
		m_birdVel.x = -m_birdVel.x;
		m_bird.setTexture(m_GameData->assets.GetTexture("BirdNormal"));

		hide1 = true;
		adding2 = true;
	}
	/////////////////////////////
	if (hide1)
	{
		for (sf::Sprite& spr : m_spikes1)
			if (spr.getPosition().x > 20.0f - spr.getLocalBounds().width)
			{
				spr.setPosition(spr.getPosition().x - 140.0f * _dt, spr.getPosition().y);

				if (adding2)
				{
					srand(time(NULL));
					for (int i = 0; i < m_spikesCount; i++)
					{
						m_spikesPos[i] = (rand() % 11) + 1;

						sf::Sprite tempSpike;
						tempSpike.setTexture(m_GameData->assets.GetTexture("SpikeRight"));
						tempSpike.setOrigin(tempSpike.getLocalBounds().width, 0.0f);

						m_spikes2.push_back(tempSpike);
					}
					adding2 = false;
				}
				else
				{
					for (int i = 0; i < m_spikesCount; i++)
					{
						m_spikes2[i].setPosition(spr.getPosition().x + (600.0f), 30.0f + (m_spikesPos[i] * 67.0f) - 67.0f);
					}
				}
			}
			else
			{
				int size = m_spikes1.size();

				m_spikes1.clear();

				hide1 = false;
			}
	}
	//////////////////////////////
	if (hide2)
	{
		for (sf::Sprite& spr : m_spikes2)
			if (spr.getPosition().x < 580.0f + spr.getLocalBounds().width)
			{
				spr.setPosition(spr.getPosition().x + 140.0f * _dt, spr.getPosition().y);

				if (adding1)
				{
					srand(time(NULL));
					for (int i = 0; i < m_spikesCount; i++)
					{
						m_spikesPos[i] = (rand() % 11) + 1;

						sf::Sprite tempSpike;
						tempSpike.setTexture(m_GameData->assets.GetTexture("SpikeLeft"));

						m_spikes1.push_back(tempSpike);
					}
					adding1 = false;
				}
				else
				{
					for (int i = 0; i < m_spikesCount; i++)
					{
						m_spikes1[i].setPosition(spr.getPosition().x - (600.0f), 30.0f + (m_spikesPos[i] * 67.0f) - 67.0f);
					}
				}
			}
			else
			{
				int size = m_spikes2.size();

				m_spikes2.clear();

				hide2 = false;
			}
	}
}

void GameState::Draw(float _dt)
{
	m_GameData->window.clear();

	m_GameData->window.draw(m_background);
	m_GameData->window.draw(m_score);
	m_GameData->window.draw(m_bird);

	for (sf::Sprite spr : m_spikes1)
		m_GameData->window.draw(spr);
	for(sf::Sprite spr : m_spikes2)
		m_GameData->window.draw(spr);

	m_GameData->window.display();
}

void GameState::AddScore()
{
	m_scoreCount++;

	if (m_scoreCount < 10)
		m_scoreString = "0" + std::to_string(m_scoreCount);
	else
	{
		m_score.setPosition(340.0f, 330.0f);
		m_scoreString = std::to_string(m_scoreCount);
	}

	m_score.setString(m_scoreString);

	if (m_scoreCount < 2)
		m_spikesCount = 1;
	else if (m_scoreCount < 5)
		m_spikesCount = 2;
	else if (m_scoreCount < 5)
		m_spikesCount = 2;
	else if (m_scoreCount < 10)
		m_spikesCount = 3;
	else if (m_scoreCount < 20)
		m_spikesCount = 4;
	else
		m_spikesCount = 5;	
}

bool GameState::CheckColisions()
{
	sf::FloatRect birdBounds = m_bird.getGlobalBounds();		
	
	if (birdBounds.top + birdBounds.height > 747 || birdBounds.top < 53)
	{
		std::ofstream file;
		file.open("Data/data.txt", std::ios::trunc);

		if (m_scoreCount > Game::m_gBestScore)
			Game::m_gBestScore = m_scoreCount;
		if (file.is_open())
		{
			file << Game::m_gBestScore << std::endl;
			file << Game::m_gGamesPlayed << std::endl;
			file << Game::m_gBirdSkin;

			file.close();
		}

		m_GameData->stateManager.AddState(StateRef(new ResultState(m_GameData, m_scoreCount)));
		return true;
	}

	for (int i = 0; i < m_spikes2.size(); i++)
		if (m_bird.getGlobalBounds().intersects(m_spikes2[i].getGlobalBounds()))
		{
			std::ofstream file;
			file.open("Data/data.txt", std::ios::trunc);

			if (m_scoreCount > Game::m_gBestScore)
				Game::m_gBestScore = m_scoreCount;
			if (file.is_open())
			{
				file << Game::m_gBestScore << std::endl;
				file << Game::m_gGamesPlayed << std::endl;
				file << Game::m_gBirdSkin;

				file.close();
			}

			m_spikes2.clear();
			m_GameData->stateManager.AddState(StateRef(new ResultState(m_GameData, m_scoreCount)));

			return true;
		}

	for (int i = 0; i < m_spikes1.size(); i++)
		if(m_bird.getGlobalBounds().intersects(m_spikes1[i].getGlobalBounds()))
		{
			std::ofstream file;
			file.open("Data/data.txt", std::ios::trunc);

			if (m_scoreCount > Game::m_gBestScore)
				Game::m_gBestScore = m_scoreCount;
			if (file.is_open())
			{
				file << Game::m_gBestScore << std::endl;
				file << Game::m_gGamesPlayed << std::endl;
				file << Game::m_gBirdSkin;

				file.close();
			}

			m_spikes1.clear();
			m_GameData->stateManager.AddState(StateRef(new ResultState(m_GameData, m_scoreCount)));

			return true;
		}

	
	return false;
}
