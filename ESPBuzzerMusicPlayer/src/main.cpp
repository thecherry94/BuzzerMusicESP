#include <Arduino.h>
#include <EEPROM.h>


#include "CPlayer.h"
#include "CStateMachine.h"

#include "CInitialization__State.h"

CPlayer player;
CStateMachine machine;

CInitialization__State stateInit("mainMenu");

void setup() 
{
    Serial.begin(115200);
    EEPROM.begin(pow(2, 15));

    stateInit.setup(&player);
    machine.AddState(&stateInit);
}

void loop() 
{
    machine.Update();
}