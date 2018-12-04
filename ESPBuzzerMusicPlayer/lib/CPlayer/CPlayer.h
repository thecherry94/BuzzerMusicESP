#ifndef PLAYER__H
#define PLAYER__H

#include "CWebServer.h"

enum EPlayerState
{
    MAIN_MENU,
    UPLOAD_MENU
};


class CPlayer
{
    private:
        CWebServer* _server;



    public:
        CPlayer();

        CWebServer* getServer() { return _server; }


};




#endif