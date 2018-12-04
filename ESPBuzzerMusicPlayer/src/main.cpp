#include <Arduino.h>
#include <EEPROM.h>

#include <SPIFFS.h>

#include "CPlayer.h"
#include "CStateMachine.h"

#include "CInitialization__State.h"
#include "CRunning__State.h"

CPlayer player;
CStateMachine machine;

CInitialization__State stateInit("init");
CRunning__State stateRunning("running");

void setup() 
{
    Serial.begin(115200);
    EEPROM.begin(pow(2, 15));
    SPIFFS.begin();

    stateInit.setup(&player);
    stateRunning.setup(&player);

    machine.AddState(&stateInit);
    machine.AddState(&stateRunning);
}

void loop() 
{
    machine.Update();
}