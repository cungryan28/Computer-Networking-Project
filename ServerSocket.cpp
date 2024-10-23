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

void ServerSocket::handleEvent(ServerSocket &server, SOCKET &clientSocket, std::string message) {
    if (message == "SHUTDOWN") {
        WinAPI::MySystemShutdown();
    } else if (message == "RESTART") {
        LPWSTR message = L"RESTART";
        WinAPI::MySystemRestart(message);
    } else if (message == "GET API") {
        server.sendIPAddress(clientSocket);
    } else if (message == "HELLO SERVER") {
        message = "Hello from server!";
        server.sendMessage(clientSocket, &message[0]);
    } else if (message == "STOP") {
        this->~ServerSocket();
        closesocket(clientSocket);
        exit(0);
    } else {
        std::string message_to_client = "INVALID MESSAGE";
        send(clientSocket, message_to_client.c_str(), static_cast<int>(message_to_client.length()), 0);
    } 
}
