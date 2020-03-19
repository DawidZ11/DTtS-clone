#pragma once

#include <memory>
#include <stack>

#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateManager
{
	std::stack<StateRef> m_states;

public:
	StateManager() {};
	~StateManager() {};

	void AddState(StateRef _state, bool _isReplacing = true);
	void RemoveState();

	StateRef& GetActiveState();
};

