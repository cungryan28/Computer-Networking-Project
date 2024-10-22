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


    void handleMessage(SOCKET &clientSocket) {
        char buffer[1024] = {0};
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "Message from server: " << buffer << '\n';
        } else {
            std::cerr << "Failed to receive message from the server.\n";
            exit(1);
        }

        std::string s(buffer);
        if (s == "SHUTDOWN") {
            // LPTSTR message = L"Shutdown";
            Driver::MySystemShutdown();
        } else {
            std::string message_to_client = "INVALID MESSAGE";
            send(clientSocket, message_to_client.c_str(), static_cast<int> (message_to_client.length()), 0);
        }
    }

};