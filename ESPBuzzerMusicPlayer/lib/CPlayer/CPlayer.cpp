#include "CPlayer.h"
#include <Arduino.h>
#include <EEPROM.h>


CPlayer::CPlayer()
{
    _state = EPlayerState::MAIN_MENU;
}




