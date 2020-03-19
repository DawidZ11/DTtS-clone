#pragma once

#include "State.h"
#include "Game.h"

#include <vector>

enum BirdDir 
{
	BD_LEFT,
	BD_RIGHT
};

class GameState : public State
{
	GameDataRef m_GameData;

	int m_spikesCount;
	std::vector<sf::Sprite> m_spikes1;
	std::vector<sf::Sprite> m_spikes2;

	sf::Sprite m_bird;
	sf::Vector2f m_birdVel;
	BirdDir m_birdDir;

	sf::Sprite m_background;

	int m_scoreCount;
	std::string m_scoreString;
	sf::Text m_score;

	const int m_maxSpikes = 11;
	int m_spikesPos[5];

	sf::Clock m_Clock;

public:
	GameState(GameDataRef _gameData);
	~GameState();

	void Initialize();

	void HandleInput();
	void Update(float _dt);
	void Draw(float _dt);

	void AddScore();

	bool CheckColisions();
};

