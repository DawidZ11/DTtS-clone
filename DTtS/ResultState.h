#pragma once

#include "State.h"
#include "Game.h"

class ResultState : public State
{
	GameDataRef m_GameData;
	int m_finalScoreCount;

	sf::Sprite m_background;
	sf::Sprite m_result;
	sf::Sprite m_replay;

	sf::Text m_finalScore;

	sf::Text m_bestScore, m_gamesPlayed;

	sf::Clock m_Clock;

public:
	ResultState(GameDataRef _gameData, int _finalScore);
	~ResultState() { };

	void Initialize();

	void HandleInput();
	void Update(float _dt);
	void Draw(float _dt);
};

