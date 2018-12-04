#pragma once

#include <vector>

#include "etc.h"
#include "CStateMachine.h"


class CStateMachine;


class CState
{
	private:
		std::vector<sTransition> _transitions;
		std::string _name;

	protected:
		CState(std::string name);


	public:
		virtual void enter() = 0;
		virtual void process() = 0;
		virtual void leave() = 0;

		~CState();

		void CheckTransitionConditions();
		void AddTransition(sTransition);
		void SetStateMachine(CStateMachine* mach);

		CStateMachine* _pMachine;

		std::string GetName();

};