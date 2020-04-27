//
// Created by User on 3/25/2020.
//
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include "realPlayer.h"
#include "game.h"
#include "cpuPlayer.h"

game::game(int player) {
    int coins;
    this->players = player;
    this->cpu = new cpuPlayer();
    this->real = new realPlayer[player];
    for (int i = 0; i < player; i++) {
        cout << "Player " << i + 1 << endl;
        cout << "Enter begins coins to start" << endl;
        cin >> coins;
        real[i] = realPlayer(coins);
    }

}

void game::draw() {

    for (int i = 0;i < this->players;i++) {
        cout << "Player " << i + 1 << " cards:" << endl;
        cout << "  ";
        real[i].showCards();
        cout << "  the sum: " << real[i].getSumCards();
        cout << endl;
        cout << " " << "Bet on this round: ";
        cout << real[i].getPerCoins() << endl;
        cout << "Coins: ";
        real[i].showCoins();
        cout << endl;
        cout << "-----------------------" << endl;
    }
    cout << "The dealer cards: " << endl;
    cout << " ";
    cpu->showCards();
    cout << " the sum: " << cpu->getSumCards();
    cout << endl;
    cout << "-----------------------" << endl;

}



int game::start() {
    int choose;
    int chCOfO;
    int first = 0;
    int co;
    int isGame = this->players;
    while (isGame > 0) {
        if (first == 0) {
            first = 1;
        }
        else {
            for (int i = 0;i < players;i++) {
                if (real[i].getCoins() == 0) {
                    real[i].setForfeit(true);
                    isGame--;
                }
                if (real[i].getForfeit() == false) {
                    cout << "Player " << i + 1 << " choose :" << endl;
                    cout << "1.Stay for more round" << endl;
                    cout << "2.Exit" << endl;
                    do {
                        cin >> chCOfO;
                        if (chCOfO == 2 || chCOfO == 1) {
                            break;
                        }
                        cout << "Your choose is wrong, choose again " << endl;
                        cout << "1.Stay for more round" << endl;
                        cout << "2.Exit" << endl;
                    } while (1);

                    if (chCOfO == 2) {
                        real[i].setForfeit(true);
                        isGame--;
                    }
                }

            }
        }
        if (isGame == 0) {
            break;
        }
        game::createCards();
        cpu->newRound(this->cards);
        for (int i = 0;i < players;i++) {

            if (real[i].getForfeit() == false) {
                real[i].newRound(this->cards);
            }

        }


        for (int i = 0;i < players;i++) {
            if (real[i].getForfeit() == false) {
                do {
                    cout << "Player " << i + 1 << " bet for this round: " << endl;
                    cin >> co;
                    if (co <= real[i].getCoins()) {
                        break;
                    }
                    cout << "Your bet is wrong , bet again" << endl;
                } while (1);
                real[i].setPerRoundCoins(co);
            }

        }
        game::draw();

        for (int i = 0;i < this->players;i++) {
            choose = 2;
            if (real[i].getForfeit() != true) {
                real[i].showCards();
                cout << "  the sum:" << real[i].getSumCards();
                cout << endl;
                if (real[i].getSumCards() == 21) {
                    real[i].setFirstWin(true);
                    cout << "Player " << i + 1 << " you won the dealer" << endl;
                    real[i].setPerRoundCoins(real[i].getPerCoins() * 2);
                    real[i].changeCoins();
                }
                else {
                    while (real[i].getSumCards() < 21 && choose == 2) {
                        cout << "Player " << i + 1 << " choose option: " << endl;
                        cout << "1.Stay" << endl;
                        cout << "2.Hit" << endl;
                        cout << "3.Double" << endl;
                        cin >> choose;
                        switch (choose) {
                        case 1: {
                            break;
                        }
                        case 2: {
                            real[i].addCard(this->cards);
                            real[i].showCards();
                            cout << "  the sum:" << real[i].getSumCards();
                            cout << endl;
                            break;
                        }
                        case 3: {
                            if (real[i].getPerCoins() * 2 <= real[i].getCoins()) {
                                real[i].addCard(this->cards);
                                real[i].doubleCoins();
                                real[i].showCards();
                                cout << "  the sum:" << real[i].getSumCards() << endl;

                            }
                            else {
                                choose = 2;
                                cout << "You can not double your bet" << endl;
                            }

                            break;
                        }
                        default: cout << "Your choose is wrong" << endl;
                            choose = 2;
                            break;
                        }

                    }

                    if (real[i].getSumCards() > 21) {
                        cout << "Player " << i + 1 << " you lose to the dealer..." << endl;
                        co = real[i].getPerCoins() * (-1);
                        real[i].setPerRoundCoins(co);
                        real[i].changeCoins();
                        co = co * (-1);
                        real[i].setPerRoundCoins(co);
                    }

                }
                cout << "---------------------" << endl;
            }

        }

        game::draw();
        cout << "Now the dealer is playing :" << endl;
        while (cpu->getSumCards() < 17) {
            cpu->addCard(this->cards);
            Sleep(1800);
            cpu->showCards();
            cout << " the sum: " << cpu->getSumCards();
            cout << endl;


        }



        if (cpu->getSumCards() > 21) {
            cout << "All the players won the dealer!!!" << endl;
            for (int i = 0;i < players;i++) {
                if (real[i].getSumCards() <= 21 && real[i].getForfeit() == false && real[i].getFirstWin() == false) {
                    real[i].changeCoins();
                }
            }
        }
        else if (cpu->getSumCards() == 21) {
            for (int i = 0; i < players; i++) {
                if (real[i].getSumCards() < 21 && real[i].getForfeit() == false && real[i].getFirstWin() == false) {
                    cout << "Player " << i + 1 << " you lose to the dealer..." << endl;
                    co = real[i].getPerCoins() * (-1);
                    real[i].setPerRoundCoins(co);
                    real[i].changeCoins();
                }
                else if (real[i].getSumCards() == 21 && real[i].getForfeit() == false && real[i].getFirstWin() == false) {
                    cout << "Player " << i + 1 << " you tie with the dealer..." << endl;
                }

            }
        }
        else {
            for (int i = 0; i < players; i++) {
                if (real[i].getSumCards() > cpu->getSumCards() && real[i].getSumCards() <= 21 && real[i].getForfeit() == false && real[i].getFirstWin() == false) {
                    cout << "Player " << i + 1 << " you won the dealer!!!" << endl;
                    real[i].changeCoins();
                }
                else if (real[i].getSumCards() < cpu->getSumCards() && real[i].getSumCards() <= 21 && real[i].getForfeit() == false && real[i].getFirstWin() == false) {
                    cout << "Player " << i + 1 << " you lose to the dealer..." << endl;
                    co = real[i].getPerCoins() * (-1);
                    real[i].setPerRoundCoins(co);
                    real[i].changeCoins();
                }
                else if (real[i].getSumCards() <= 21 && real[i].getForfeit() == false && real[i].getFirstWin() == false) {
                    cout << "Player " << i + 1 << " you tie with the dealer :)" << endl;
                }


            }
        }


    }
    
    return 1;

}

game::~game() {
    for (int i = 0; i < players; ++i) {
        real[i].getVector().clear();
    }
    delete(cpu);
}


vector<int> game::getCards() {
    return this->cards;
}

void game::shuffleCards() {
    srand(unsigned(std::time(0)));
    random_shuffle(cards.begin(), cards.end());
    random_shuffle(cards.begin(), cards.end());
    random_shuffle(cards.begin(), cards.end());
    random_shuffle(cards.begin(), cards.end());
}

void game::createCards() {
    int count = 0, j = 2;
    if (cards.empty() == false) {
        cards.clear();
    }
    for (int i = 0;i <= 207;i++) {
        if (count == 4 * 4) {
            count = 0;
            j++;
        }
        cards.push_back(j);
        count++;
    }

    game::shuffleCards();


}