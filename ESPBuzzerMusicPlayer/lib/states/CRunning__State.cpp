#include <Arduino.h>

#include "CRunning__State.h"
#include "global.h"
#include <SPIFFS.h>


CRunning__State::CRunning__State(std::string name)
    : CState(name)
{
    
}


void CRunning__State::setup(CPlayer* player)
{
    _player = player;
    _server = _player->getServer();
}


void CRunning__State::enter()
{
    DEBUG_PRINT("CRunning__State::enter\n");

    _server->addURL("/", [&](AsyncWebServerRequest* req)
    {
        req->send(SPIFFS, "/html/index.html");
    });
}



void CRunning__State::process()
{
    
}



void CRunning__State::leave()
{
    DEBUG_PRINT("CRunning__State::leave\n");
}





