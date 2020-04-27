//
// Created by User on 3/25/2020.
//
#include <vector>
#include <string>

#ifndef BLACKJACK_BLACK_H
#define BLACKJACK_BLACK_H





class realPlayer{
private:

    int coins;
    int perRoundCoins;
    bool forfeit;
    bool firstWin;
    int sum;

public:
    ~realPlayer();
    realPlayer();
    realPlayer(int coins);
    void showCards(char v[8][8],int size);
    void doubleCoins();
    void showCoins();
    void setPerRoundCoins(int co);
    int getCoins();
    int getPerCoins();
    bool getFirstWin();
    void setFirstWin(bool t);
    bool getForfeit();
    void setForfeit(bool t);
    void changeCoins();
    void setSumCards(char v[8][8],int size);
    int getSumCards();


};


#endif //BLACKJACK_BLACK_H
