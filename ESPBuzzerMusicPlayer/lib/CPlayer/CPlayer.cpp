#include "CPlayer.h"
#include <Arduino.h>
#include <EEPROM.h>


CPlayer::CPlayer()
{
    _server = new CWebServer();
}




