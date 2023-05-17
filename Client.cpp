#include <iostream>
#include <string>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) 

#define SERVER_IP "127.0.0.1"
#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return -1;
    }

    // Create socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddress.sin_port = htons(PORT);

    while (true) {
        // Read input from the user
        std::cout << "Enter message: ";
        std::string message;
        std::getline(std::cin, message);

        // Send data to server
        int sendResult = sendto(clientSocket, message.c_str(), message.size(), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
        if (sendResult == SOCKET_ERROR) {
            std::cerr << "Failed to send data: " << WSAGetLastError() << std::endl;
            break;
        }

        // Receive data from server
        int serverAddressSize = sizeof(serverAddress);
        int recvResult = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&serverAddress, &serverAddressSize);
        if (recvResult == SOCKET_ERROR) {
            std::cerr << "Failed to receive data: " << WSAGetLastError() << std::endl;
            break;
        }

        // Print received data
        std::cout << "Received from server: " << buffer << std::endl;
    }

    // Cleanup
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
