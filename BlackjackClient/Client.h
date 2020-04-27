#pragma once
#include "iClient.h"
#include <iostream>
#include <sstream>
class Client :
	public iClient
{
public:
	Client();
	virtual int connectToServer(std::string ip, unsigned short port);
	virtual int sendData(char* data, int size);
	virtual void* receiveData();
	virtual int closeConnection();
};

