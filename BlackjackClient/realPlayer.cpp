//
// Created by User on 3/25/2020.
//
#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include "realPlayer.h"

using namespace std;

realPlayer::realPlayer(int coins) {
    this->forfeit = false;
    this->firstWin = false;
    this->coins = coins;

}

void realPlayer::showCards(char  v[8][8],int size)
{
    for (int i = 0;i < size;i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}


void realPlayer::doubleCoins() {
    this->perRoundCoins = this->perRoundCoins * 2;
}

void realPlayer::showCoins() {
    cout << coins;
}

realPlayer::realPlayer() {
    this->forfeit = false;
    this->firstWin = false;
}

void realPlayer::setPerRoundCoins(int co) {
    this->perRoundCoins = co;
}

int realPlayer::getCoins() {
    return this->coins;
}

int realPlayer::getPerCoins() {
    return this->perRoundCoins;
}


void realPlayer::changeCoins() {
    this->coins += this->perRoundCoins;
}

void realPlayer::setSumCards(char v[8][8], int size)
{
    int temp, countA = 0;
    this->sum = 0;
    for (int i =0; i <size; i++) {
        if (strcmp(v[i],"2")==0  || strcmp(v[i], "3") == 0 || strcmp(v[i], "4") == 0 || strcmp(v[i], "5") == 0 || strcmp(v[i], "6") == 0 || strcmp(v[i], "7") == 0 || strcmp(v[i], "8") == 0 || strcmp(v[i], "9") == 0 || strcmp(v[i], "10") == 0) {
            temp = atoi(v[i]);
            sum += temp;
        }
        else {
            if (strcmp(v[i], "A") != 0) {
                sum += 10;
            }
            else {
                countA++;
            }
        }

    }
    if (countA == 1) {
        if (sum + 11 > 21) {
            sum += 1;
        }
        else {
            sum += 11;
        }
    }
    else if (countA == 2) {
        if (sum + 12 > 21) {
            sum += 2;
        }
        else {
            sum += 12;
        }
    }
    else if (countA == 3) {
        if (sum + 13 > 21) {
            sum += 3;
        }
        else {
            sum += 13;
        }
    }
    else if (countA == 4) {
        if (sum + 14 > 21) {
            sum += 4;
        }
        else {
            sum += 14;
        }
    }

}

int realPlayer::getSumCards()
{
    return this->sum;
}



realPlayer::~realPlayer() {
    
}


bool realPlayer::getForfeit() {
    return this->forfeit;
}

void realPlayer::setForfeit(bool t) {
    this->forfeit = t;
}

bool realPlayer::getFirstWin() {
    return this->firstWin;
}

void realPlayer::setFirstWin(bool t) {
    this->firstWin = t;
}

