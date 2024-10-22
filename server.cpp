#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define SERVER_IP "127.0.0.1"

class ServerSocket {
private:
    SOCKET serverSocket;
    struct sockaddr_in serverAddress;
public:
    ServerSocket() {
        WSADATA wsaSATA;
        if (WSAStartup(MAKEWORD(2, 2), &wsaSATA) != 0) {
            std::cerr << "WSAStartup failed.\n";
            exit(1);
        }
        
        // Creating server socket
        serverSocket = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
        if (serverSocket == -1) {
            std::cerr << "Socket creation failed.\n";
            exit(1);
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(PORT);

        // Bind
        if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
            std::cerr << "Bind failed: " << WSAGetLastError() << '\n';
            exit(1);
        }

        // Listen to connection from client
        if (listen(serverSocket, 5) == -1) {
            std::cerr << "Listen failed: " << WSAGetLastError() << '\n';
            exit(1);
        }

        std::cout << "Server is listening on port " << PORT << "...\n";

    }

    ~ServerSocket() {
        closesocket(serverSocket);
        WSACleanup();
    }

    void sendIPAddress(int &clientSocket) {
        const char* ipAddress = SERVER_IP;
        send(clientSocket, ipAddress, static_cast<int>(strlen(ipAddress)), 0);
        std::cout << "Sending IP address: " << ipAddress << std::endl;
    }

    void sendMessage(int &clientSocket, const char* message) {
        send(clientSocket, message, static_cast<int>(strlen(message)), 0);
    }

    SOCKET getSocket() {
        return serverSocket;
    }
};

int main() {
    ServerSocket server;

    // Accept conection from client
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    int clientSocket = static_cast<int>(accept(server.getSocket(), (struct sockaddr*)&clientAddress, &clientAddressLen));
    if (clientSocket < 0) {
        std::cerr << "Accept failed.\n";
        return 1;
    }

    server.sendMessage(clientSocket, "Hello from server!");
    std::cout << "Message sent to client.\n";

    server.sendIPAddress(clientSocket);
    std::cout << "IPAddress sent to client.\n";


    closesocket(clientSocket);

}