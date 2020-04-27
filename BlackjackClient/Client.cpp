#include "Client.h"

Client::Client() :iClient()
{
}

int Client::connectToServer(std::string serverIp, unsigned short port)
{
    isServerConnected = true;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    std::ostringstream oss;
    oss << port;

    iResult = getaddrinfo(serverIp.c_str(), oss.str().c_str(), &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        isServerConnected = false;
        return 0;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL;ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 0;
    }
    return 1;
}

int Client::sendData(char* data, int size)
{
    iResult = send(ConnectSocket, data, size, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 0;
    }
    return 1;
}

void* Client::receiveData()
{
    memset(&recvbuf, 0, sizeof(recvbuf));
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0)
    {
        return recvbuf;

    }
    else {
        printf("unable to get!!\n");
        return nullptr;
    }


}

int Client::closeConnection()
{
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    return 1;
}
