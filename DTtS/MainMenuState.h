#pragma once

#include "Game.h"
#include "State.h"


class MainMenuState : public State
{
	GameDataRef m_GameData;

	sf::Sprite m_background;

	sf::Sprite m_bird;
	float m_birdY;
	float m_birdVel;

	sf::Text m_bestScore, m_gamesPlayed;

	sf::Clock m_Clock;

public:
	MainMenuState(GameDataRef _gameData);
	~MainMenuState() { };

	void Initialize();

	void HandleInput();
	void Update(float _dt);
	void Draw(float _dt);
};

