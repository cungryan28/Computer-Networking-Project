#include "ServerSocket.hpp"


ServerSocket::ServerSocket() {
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