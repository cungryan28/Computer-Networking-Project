#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#define PORT 8080
#define SERVER_IP "127.0.0.1"

class ServerSocket {
private:
    struct sockaddr_in serverAddress;
public:
    int serverSocket;
    ServerSocket() {
#ifdef _WIN32
        WSADATA wsaSATA;
        if (WSAStartup(MAKEWORD(2, 2), &wsaSATA) != 0) {
            std::cerr << "WSAStartup failed.\n";
            exit(1);
        }
#endif
        
        // Creating server socket
        serverSocket = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
        if (serverSocket == -1) {
            std::cerr << "Socket creation failed.\n";
            exit(1);
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(PORT);

        // Blind
        if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
#ifdef _WIN32
            std::cerr << "Bind failed: " << WSAGetLastError() << '\n';
#else
            std::cerr << "Bind failed: " << strerror(errno) << '\n';
#endif
            exit(1);
        }

        // Listen to connection from client
        if (listen(serverSocket, 5) == -1) {
#ifdef _WIN32
            std::cerr << "Listen failed: " << WSAGetLastError() << '\n';
#else
            std::cerr << "Listen failed: " << strerror(errno) << '\n';
#endif
            exit(1);
        }

        std::cout << "Server is listening on port " << PORT << "...\n";

    }
    ~ServerSocket() {
#ifdef _WIN32
        closesocket(serverSocket);
        WSACleanup();
#else
        close(serverSocket);
#endif
    }
    void sendIPAddress(int &clientSocket) {
        const char* ipAddress = SERVER_IP;
        send(clientSocket, ipAddress, static_cast<int>(strlen(ipAddress)), 0);
        std::cout << "Sending IP address: " << ipAddress << std::endl;
    }
    void sendMessage(int &clientSocket, const char* message) {
        send(clientSocket, message, static_cast<int>(strlen(message)), 0);
    }
    int getSocket() {
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

    std::cout << "Check 1\n";

    server.sendMessage(clientSocket, "Hello from server!");
    std::cout << "Message sent to client.\n";

    std::cout << "Check 2\n";

    server.sendIPAddress(clientSocket);
    std::cout << "IPAddress sent to client.\n";


    // Close socket
#ifdef _WIN32
    closesocket(clientSocket);
#else
    close(clientSocket);
#endif

}