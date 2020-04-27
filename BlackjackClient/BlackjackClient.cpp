#define WIN32_LEAN_AND_MEAN

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>



#include "realPlayer.h"
#include "Client.h"
#include "Inform.h"
#include "GameTable.h"


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


using namespace std;

int main() {
    int coins;
    int choose;
    int con;
    int firstGame = 0;
    enum_result res;;
    GameTable* game;
    char data[BUFSIZ];
    string temp;
    char buffer[BUFSIZ];
    int size;
    game = new GameTable();

    std::cout << "enter your coins" << std::endl;
    std::cin >> coins;
    game->start(coins);
    while (1) {
        if (firstGame == 0) {
            firstGame = 1;
        }
        else {
           
            game->forefitMatch();
        }
        if (game->getPlayer()->getForfeit() == true) {
            break;
        }
        game->newRound();
        game->modeGame();
        res=game->check();
        if (res == win) {
            game->getPlayer()->setPerRoundCoins(game->getPlayer()->getPerCoins() * 2);
            game->winGame();
        }
        else {
            do {
                con = game->playMove();
                game->modeGame();
                res=game->check();
                if (res == lose) {
                    game->loseGame();
                    break;
                }

            } while (con==1);

            if (res != lose) {
                cout << "Now the dealer is playing" << endl;
                do {
                    game->dealerMove();
                    res=game->check();
                   } while (res==stillPlay);

                if (res == win) {
                    game->winGame();
                }
                else if (res == lose) {
                    game->loseGame();
                }
                else {
                    game->tieGame();
                }
                
            }
            
            
        }

        if (game->getPlayer()->getCoins() == 0) {
            game->getPlayer()->setForfeit(true);
         }
     }


    
    
    delete game;

    
            return 0;
}


