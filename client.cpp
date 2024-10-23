#include "ClientSocket.hpp"
#include <fstream>
#include <string>

int main() {
    ClientSocket client;
    char buffer[1024] = {0};
    int bytesReceived = 0;

    while (true) {
        std::string userInput;
        std::cout << "Enter message to send to server: ";
        std::getline(std::cin, userInput);

        if (userInput.empty()) {
            continue;
        } else if (userInput == "STOP") {
            break;
        }

        send(client.getSocket(), userInput.c_str(), static_cast<int>(userInput.length()), 0);

        memset(buffer, 0, sizeof(buffer));
        bytesReceived = recv(client.getSocket(), buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "\t-> Response from server: " << buffer << '\n';
        } else {
            std::cerr << "\t-> Failed to receive response from the server.\n";
        }

    }

    return 0;
}