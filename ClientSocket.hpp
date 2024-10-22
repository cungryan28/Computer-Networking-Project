#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define SERVER_IP "127.0.0.1"

class ClientSocket {
private:
    SOCKET clientSocket;
    struct sockaddr_in serverAddress;
public:
    ClientSocket();

    ~ClientSocket() {
        closesocket(clientSocket);
        WSACleanup();
    }

    SOCKET getSocket() {
        return clientSocket;
    }
};