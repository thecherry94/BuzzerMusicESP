#ifndef PLAYER__H
#define PLAYER__H



enum EPlayerState
{
    MAIN_MENU,
    UPLOAD_MENU
};


class CPlayer
{
    private:
        EPlayerState _state;



    public:
        CPlayer();


};




#endif