#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

// Define your struct
struct MyStruct {
    int id;
    std::string name;
    double value;
};

// Function to send struct over UDP
bool sendStructOverUDP(const MyStruct& obj, const std::string& ipAddress, int port) {
    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return false;
    }

    // Prepare the server address
    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ipAddress.c_str(), &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Invalid IP address" << std::endl;
        close(sockfd);
        return false;
    }

    // Convert struct to a buffer
    char buffer[sizeof(MyStruct)];
    std::memcpy(buffer, &obj, sizeof(MyStruct));

    // Send the buffer over UDP
    ssize_t bytesSent = sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (bytesSent < 0) {
        std::cerr << "Failed to send data" << std::endl;
        close(sockfd);
        return false;
    }

    std::cout << "Struct sent successfully" << std::endl;

    // Close the socket
    close(sockfd);

    return true;
}

int main() {
    MyStruct myStruct { 1, "Example", 3.14 };
    std::string ipAddress = "127.0.0.1";  // IP address of the destination
    int port = 1234;                      // Port number

    if (sendStructOverUDP(myStruct, ipAddress, port)) {
        std::cout << "Struct sent over UDP successfully" << std::endl;
    } else {
        std::cerr << "Failed to send struct over UDP" << std::endl;
    }

    return 0;
}
