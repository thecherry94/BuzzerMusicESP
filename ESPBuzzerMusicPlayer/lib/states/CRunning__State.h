#pragma once





#include "CState.h"

#include "CPlayer.h"
#include "CWebServer.h"


class CRunning__State : public CState
{
    private:
        CPlayer* _player;
        CWebServer* _server;


    public:
        CRunning__State(std::string name);

        void setup(CPlayer* player);

        void setup() {};
        void enter() override;
        void process() override;
        void leave() override;
};