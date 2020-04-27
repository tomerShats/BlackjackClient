#pragma once
#include <vector>
#include <string>
#include<iostream>
#include "realPlayer.h"
#include "Client.h"
#include "Inform.h"


class GameTable
{
    private:
        realPlayer* player;
        NewGame newGame;
        cards * m_cards;
        yourMove m_move;
        iClient* client;
        void draw();


    public:
        ~GameTable();
        GameTable();
        realPlayer * getPlayer();
        int start(int coins);
        void newRound();
        void modeGame();
        enum_result check();
        void winGame();
        void loseGame();
        void tieGame();
        void forefitMatch();
        int playMove();
        void dealerMove();



};

