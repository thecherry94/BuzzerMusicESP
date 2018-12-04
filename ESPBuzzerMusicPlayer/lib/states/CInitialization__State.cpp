#include <Arduino.h>

#include "CInitialization__State.h"


CInitialization__State::CInitialization__State(std::string name)
    : CState(name)
{

}


void CInitialization__State::setup(CPlayer* player)
{
    _player = player;
    _server = new CWebServer();
}


void CInitialization__State::enter()
{
    Serial.println("CInitialization__State::enterdd");

    _server->connectToAP("Cherry", "4991Pk1994");
}



void CInitialization__State::process()
{
    
}



void CInitialization__State::leave()
{
    Serial.println("CInitialization__State::leave");
}





