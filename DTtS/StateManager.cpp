#include "StateManager.h"

void StateManager::AddState(StateRef _state, bool _isReplacing)
{
	if (!m_states.empty())
	{
		if (_isReplacing)
			m_states.pop();
		else
			m_states.top()->Pause();
	}
	m_states.push(std::move(_state));
	m_states.top()->Initialize();
}

void StateManager::RemoveState()
{
	if (!m_states.empty())
	{
		m_states.pop();

		if (!m_states.empty())
		{
			m_states.top()->Resume();
		}
	}
}

StateRef& StateManager::GetActiveState()
{
	return m_states.top();
}
