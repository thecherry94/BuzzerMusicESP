#include "CState.h"

CState::CState(std::string name)
{
	_name = name;
}

CState::~CState()
{

}

void CState::CheckTransitionConditions()
{
	for (int i = 0; i < _transitions.size(); i++)
	{
		sTransition* t = &_transitions[i];

		if (_pMachine->StateExists(t->stateTo))
		{
			if (t->transitionCondition)
			{
				if (t->transitionCondition())
				{
					_pMachine->TriggerTransition(*t);
				}
			}
		}
		else
		{
			#ifdef __DEBUG___
				Serial.printf("STATE %s EXISTIERT NICHT\n", t->stateTo);
			#endif
		}
	}
}

void CState::AddTransition(sTransition t)
{
	_transitions.push_back(t);
}

void CState::SetStateMachine(CStateMachine* mach)
{
	_pMachine = mach;
}

std::string CState::GetName()
{
	return _name;
}