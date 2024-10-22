#include "ServerSocket.hpp"
#include "ServerDriver.hpp"

int main() {
    ServerSocket server;

    // Accept conection from client
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    SOCKET clientSocket = static_cast<int>(accept(server.getSocket(), (struct sockaddr*)&clientAddress, &clientAddressLen));
    if (clientSocket < 0) {
        std::cerr << "Accept failed.\n";
        return 1;
    }

    server.sendMessage(clientSocket, "Hello from server!");
    std::cout << "Message sent to client.\n";

    server.sendIPAddress(clientSocket);
    std::cout << "IPAddress sent to client.\n";

    server.handleMessage(clientSocket);

    closesocket(clientSocket);

}