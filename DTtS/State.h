#pragma once

#include <SFML/Graphics.hpp>

class State
{
public:
	virtual void Initialize() = 0;

	virtual void HandleInput() = 0;
	virtual void Update(float _dt) = 0;
	virtual void Draw(float _dt) = 0;

	virtual void Pause() {};
	virtual void Resume() {};
};

