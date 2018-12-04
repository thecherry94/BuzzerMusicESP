#include <Arduino.h>

#include "CInitialization__State.h"
#include "global.h"
#include <SPIFFS.h>


CInitialization__State::CInitialization__State(std::string name)
    : CState(name)
{
    sTransition tran_init2Running;
    tran_init2Running.stateFrom = "init";
    tran_init2Running.stateTo = "running";
    tran_init2Running.transitionAction = []{ DEBUG_PRINT("Transitioning from [init] to [running] state\n"); };
    tran_init2Running.transitionCondition = [this]() { return WiFi.status() == WL_CONNECTED && _server->isReady(); };

    AddTransition(tran_init2Running);
}


void CInitialization__State::setup(CPlayer* player)
{
    _player = player;
    _server = _player->getServer();
}


void CInitialization__State::enter()
{
    DEBUG_PRINT("CInitialization__State::enter\n");

    _player->getServer()->connectToAP("Cherry", "4991Pk1994");    
}



void CInitialization__State::process()
{
    
}



void CInitialization__State::leave()
{
    DEBUG_PRINT("CInitialization__State::leave\n");
}





