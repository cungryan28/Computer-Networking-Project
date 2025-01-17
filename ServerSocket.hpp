#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "ServerDriver.hpp"

#define PORT 8080
#define SERVER_IP "127.0.0.1"

class ServerSocket {
private:
    SOCKET serverSocket;
    struct sockaddr_in serverAddress;
public:
    ServerSocket();

    ~ServerSocket() {
        closesocket(serverSocket);
        WSACleanup();
    }

    void sendIPAddress(SOCKET &clientSocket) {
        const char* ipAddress = SERVER_IP;
        send(clientSocket, ipAddress, static_cast<int>(strlen(ipAddress)), 0);
        std::cout << "Sending IP address: " << ipAddress << std::endl;
    }

    void sendMessage(SOCKET &clientSocket, const char* message) {
        send(clientSocket, message, static_cast<int>(strlen(message)), 0);
    }

    SOCKET getSocket() {
        return serverSocket;
    }

    void handleEvent(ServerSocket &server, SOCKET &clientSocket, std::string message);

};