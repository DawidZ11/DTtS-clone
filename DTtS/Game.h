#pragma once

#include <memory>
#include <string>

#include "StateManager.h"
#include "InputManager.h"
#include "AssetManager.h"

struct GameData
{
	sf::RenderWindow window;
	StateManager stateManager;
	InputManager input;
	AssetManager assets;
};

enum BirdSkin
{
	Bird_Standard
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
	const float m_dt = 1.0f / 60.0f;

	sf::Clock m_Clock;
	GameDataRef m_GameData = std::make_shared<GameData>();

public:
	static int m_gGamesPlayed;
	static int m_gBestScore;
	static BirdSkin m_gBirdSkin;

public:
	Game(int _width, int _height, const std::string& _title);
	~Game() {};

private:
	void Run();
};