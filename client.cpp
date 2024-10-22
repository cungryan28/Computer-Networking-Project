#include <iostream>
#include <cstring>
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
    ClientSocket() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed.\n";
            exit(1);
        }
        
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Socket creation failed.\n";
            WSACleanup();
            exit(1);
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT);
        if (inet_pton(AF_INET, SERVER_IP, &serverAddress.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported.\n";
            closesocket(clientSocket);
            WSACleanup();
            exit(1);
        }

        if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
            std::cerr << "Connection to server failed.\n";
            closesocket(clientSocket);
            WSACleanup();
            exit(1);
        }
    }
    ~ClientSocket() {
        closesocket(clientSocket);
        WSACleanup();
    }

    SOCKET getSocket() {
        return clientSocket;
    }
};

int main() {
    ClientSocket client;

    char buffer[1024] = {0};
    int bytesReceived = recv(client.getSocket(), buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Message from server: " << buffer << '\n';
    } else {
        std::cerr << "Failed to receive message from the server.\n";
        return 1;
    }

    memset(buffer, 0, sizeof(buffer));

    int bytesRead = recv(client.getSocket(), buffer, sizeof(buffer) - 1, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Server IP Address: " << buffer << std::endl;
    } else {
        std::cerr << "Failed to receive data from the server.\n";
        return 1;
    }

    return 0;
}