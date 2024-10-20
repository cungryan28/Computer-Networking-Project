#include <iostream>
#include <cstring>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define PORT 8080
#define SERVER_IP "127.0.0.1"

class ClientSocket {
private:
    int clientSocket;
    struct sockaddr_in serverAddress;
public:
    ClientSocket() {
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed.\n";
            exit(1);
        }
#endif
        clientSocket = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
        if (clientSocket == -1) {
            std::cerr << "Socket creation failed.\n";
            exit(1);
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(PORT);
        if (inet_pton(AF_INET, SERVER_IP, &serverAddress.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported.\n";
            exit(1);
        }

        if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
            std::cerr << "Connection to server failed.\n";
            exit(1);
        }
    }
    ~ClientSocket() {
#ifdef _WIN32
        closesocket(clientSocket);
        WSACleanup();
#else
        close(clientSocket);
#endif
    }

    int getSocket() {
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