#define _CRT_SECURE_NO_WARNINGS

#include "GameTable.h"


void GameTable::draw()
{
    cout << "Your coins: " << player->getCoins();
    cout << " Your cards: ";
    this->player->showCards(m_cards->myCards,m_cards->sizeP);
    player->setSumCards(m_cards->myCards, m_cards->sizeP);
    cout << " The sum: " << player->getSumCards()<<endl;
    cout << "Bet this round: " << player->getPerCoins()<<endl;
    cout << "-----------------------" << endl;
    cout << "The dealer cards: ";
    this->player->showCards(m_cards->dealerCards, m_cards->sizeD);
    player->setSumCards(m_cards->dealerCards, m_cards->sizeD);
    cout << " The sum: " << player->getSumCards() << endl;

}

GameTable::~GameTable()
{
	delete player;
    cout << "Closing Connection" << endl;
    client->closeConnection();
    delete client;
    delete m_cards;
}

GameTable::GameTable()
{
    client = new Client();
    client->connectToServer("127.0.0.1", 3200);
    m_cards = new cards;

}

realPlayer * GameTable::getPlayer()
{
	return this->player;
}

int GameTable::start(int coins)
{
	player = new realPlayer(coins);
	return 0;
}

void GameTable::newRound()
{
    
    int coinsT,size;
    char buffer[BUFSIZ];
    cout << "Bet for this round" <<endl;
    do {
        cin >> coinsT;
        if (coinsT <= this->getPlayer()->getCoins()) {
            break;
        }
        cout << "Bet again" << endl;
    } while (1);
    
    player->setPerRoundCoins(coinsT);
    newGame.coins = coinsT;
    newGame.stayToPlay = true;
    size = sizeof(NewGame);
    memcpy(&buffer, &newGame, size);
    client->sendData(buffer, size);

}

void GameTable::modeGame()
{
    int size;
    size = sizeof(cards);
    memcpy(m_cards, client->receiveData(), size);
  
    GameTable::draw();

}

enum_result GameTable::check()
{
   if (m_cards->struct_result.r == win) {
        return win;
    }
    else if (m_cards->struct_result.r == lose) {
        return lose;
    }
    else if (m_cards->struct_result.r == tie) {
        return tie;
    }
    else {
        return stillPlay;
    }
   
}

void GameTable::winGame()
{
    int co = m_cards->struct_result.coins;
    this->player->setPerRoundCoins(co);
    this->player->changeCoins();
    cout << "You won the dealer!!!" << endl;
}

void GameTable::loseGame()
{
    int co=m_cards->struct_result.coins;
    this->player->setPerRoundCoins(co);
    this->player->changeCoins();
    cout << "You lose the dealer..." << endl;

}

void GameTable::tieGame()
{
    cout << "You did tie with the dealer" << endl;
}

void GameTable::forefitMatch()
{
    int chooce,size;
    char buffer[BUFSIZ];
    if (this->getPlayer()->getForfeit() == true) {
        newGame.coins = 0;
        newGame.stayToPlay = false;
        size = sizeof(NewGame);
        memcpy(&buffer, &newGame, size);
        client->sendData(buffer, size);
        return;

    }

    cout << "Do you want to stay for one round more?" << endl;
    cout << "1.Stay" << endl;
    cout << "2.Exit" << endl;
    cin >> chooce;
    while (chooce < 1 || chooce > 2) {
        cout << "Your choose is wrong, choose again" << endl;
        cin >> chooce;
    }
    if (chooce == 2) {
        this->player->setForfeit(true);
        newGame.coins = 0;
        newGame.stayToPlay = false;
        size = sizeof(NewGame);
        memcpy(&buffer, &newGame, size);
        client->sendData(buffer, size);

    }

}

int GameTable::playMove()
{
    int choose,size;
    char buffer[BUFSIZ];
    cout << "Choose your move" << endl;
    cout << "1.Hit" << endl;
    cout << "2.Stay" << endl;
    cout << "3.Double" << endl;
    cin >> choose;

    while (choose < 1 || choose > 3) {
        cout << "Your choose is wrong, choose again" << endl;
        cin >> choose;

    }
    
    this->m_move.m = (enum_move)choose;
    size = sizeof(yourMove);
    memcpy(&buffer, &m_move, size);
    client->sendData(buffer, size);
    return choose;

}

void GameTable::dealerMove()
{
    int size;
    size = sizeof(cards);
    memcpy(m_cards, client->receiveData(), size);
    cout << "The dealer cards: ";
    player->showCards(m_cards->dealerCards,m_cards->sizeD);
    player->setSumCards(m_cards->dealerCards, m_cards->sizeD);
    cout << " The sum: " << player->getSumCards() << endl;

}
