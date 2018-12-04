#pragma once





#include "CState.h"

#include "CPlayer.h"
#include "CWebServer.h"


class CInitialization__State : public CState
{
    private:
        CPlayer* _player;
        CWebServer* _server;


    public:
        CInitialization__State(std::string name);

        void setup(CPlayer* player);

        void enter() override;
        void process() override;
        void leave() override;
};