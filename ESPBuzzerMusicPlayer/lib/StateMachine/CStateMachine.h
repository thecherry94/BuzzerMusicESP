#pragma once


#include "CState.h"

#include <map>

class CState;

class CStateMachine
{
	private:
		std::map<std::string, CState*> _states;
		CState* _pActiveState;
		CState* _pPreviousState;

		bool _1stUpdate;

	public:
		CStateMachine();
		void TriggerTransition(sTransition t);
		void Update();
		bool StateExists(std::string name);

		void AddState(CState* state);
};