#include "socketCommunication.hpp"
#include <iostream>

// Example callback function to process incoming data (e.g., print the data)
void printData(const std::vector<uint8_t>& data, int client_id) {
    std::cout << "Received from client " << client_id << ": ";
    for (auto byte : data) {
        std::cout << byte;
    }
    std::cout << std::endl;
}

int main() {
    try {
        // Initialize server communication
        SocketCommunication server(Role::SERVER);
        server.initialize();

        // Register a callback to process the data (in this case, just printing the data)
        server.registerCallback(printData);

        // The server will continue running, handling multiple clients
        std::this_thread::sleep_for(std::chrono::hours(100)); // Simulate long-running server
        server.deInit(); // Cleanup after server shutdown

    } catch (const std::exception& ex) {
        std::cerr << "Server error: " << ex.what() << std::endl;
        return 1;
    }
}
