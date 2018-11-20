#ifndef STATEMACHINE__H
#define STATEMACHINE__H


#include <map>

#include "CState.h"



class CStateMachine
{
    private:
        std::map<const char*, CState> _states;


    public:
        CStateMachine();


};




#endif