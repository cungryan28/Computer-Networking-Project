#include "ServerSocket.hpp"
#include <thread>
#include <vector>

// Function to handle client connection
void handleClientConnection(ServerSocket &server, SOCKET &clientSocket) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    clientSocket = static_cast<int>(accept(server.getSocket(), (struct sockaddr*)&clientAddress, &clientAddressLen));
    // Accept connection from client
    if (clientSocket < 0) {
        std::cerr << "Accept failed.\n";
        return;
    }

    char buffer[1024] = {0};
    int bytesReceived = 0;
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "\t-> Response from server: " << buffer << '\n';
            std::string message(buffer);
            server.handleEvent(server, clientSocket, message);
        } else {
            std::cerr << "\t-> Failed to receive response from the server.\n";
            break;
        }
    }
    closesocket(clientSocket);
}

int main() {
    ServerSocket server;
    SOCKET clientSocket;

    std::thread serverThread(handleClientConnection, std::ref(server), std::ref(clientSocket));
    serverThread.join();

    return 0;
}