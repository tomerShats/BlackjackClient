//
// Created by User on 3/25/2020.
//
#include <vector>
#include <string>
#include "realPlayer.h"
#include "cpuPlayer.h"
#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H
using namespace std;

class game {
private:
    realPlayer* real;
    cpuPlayer* cpu;
    int players;
    vector<int>cards;

public:
    ~game();
    game(int player);
    int start();
    void draw();
    vector<int> getCards();
    void shuffleCards();
    void createCards();


};




#endif //BLACKJACK_GAME_H
