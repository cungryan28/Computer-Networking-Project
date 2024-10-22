#include "ClientSocket.hpp"

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

    std::string s = "SHUTDOWN";
    send(client.getSocket(), s.c_str(), static_cast<int>(s.length()), 0);

    return 0;
}