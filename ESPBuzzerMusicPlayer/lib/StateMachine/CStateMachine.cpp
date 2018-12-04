#include "CStateMachine.h"

void CStateMachine::Update()
{
	if (_pActiveState != nullptr)
	{
		if (_1stUpdate)
		{
			_pActiveState->enter();
			_1stUpdate = false;
		}

		_pActiveState->CheckTransitionConditions();
		_pActiveState->process();
	}
}

CStateMachine::CStateMachine()
{
	_pActiveState = nullptr;
	_pPreviousState = nullptr;

	_1stUpdate = true;
}

void CStateMachine::TriggerTransition(sTransition t)
{
	CState* current = _states[t.stateFrom];
	CState* next = _states[t.stateTo];



	current->leave();

	if (t.transitionAction)
		t.transitionAction();

	next->enter();



	_pActiveState = next;
	_pPreviousState = current;
}


bool CStateMachine::StateExists(std::string name)
{
	return _states.find(name) != _states.end();
}

void CStateMachine::AddState(CState * state)
{
	_states[state->GetName()] = state;
	state->SetStateMachine(this);

	if (_pActiveState == nullptr)
		_pActiveState = state;		
}
