#ifndef SOCKETCOMMUNICATION_HPP_
#define SOCKETCOMMUNICATION_HPP_

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <thread>
#include <unordered_map>
#include <mutex>
#include "iCommunication.hpp"
#include "commMode.hpp"

#define SOCKET_PATH "/tmp/uds_socket"

// Forward declaration for callback registration
typedef void (*DataCallback)(const std::vector<uint8_t>& data, int client_id);

class SocketCommunication : public ICommunication {
public:
    // Constructor to set the communication mode (SERVER or CLIENT)
    SocketCommunication(Role role) : role(role), socket_fd(-1), dataCallback(nullptr) {}

    ~SocketCommunication() {
        deInit();
    }

    void registerCallback(std::function<void(const std::vector<uint8_t>&, int)> callback) {
        dataCallback = callback;
    }


    // Initialize the communication (either as server or client)
    void initialize() override {
        if (role == Role::SERVER) {
            // Server setup
            socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
            if (socket_fd == -1) {
                throw std::runtime_error("Server socket creation failed.");
            }

            sockaddr_un server_addr{};
            server_addr.sun_family = AF_UNIX;
            strcpy(server_addr.sun_path, SOCKET_PATH);

            if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
                throw std::runtime_error("Server bind failed.");
            }

            if (listen(socket_fd, 5) == -1) {
                throw std::runtime_error("Server listen failed.");
            }

            std::cout << "Server is listening on " << SOCKET_PATH << std::endl;

            // Accept client connections in a separate thread
            std::thread([this]() { this->acceptClients(); }).detach();
        } else if (role == Role::CLIENT) {
            // Client setup
            socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
            if (socket_fd == -1) {
                throw std::runtime_error("Client socket creation failed.");
            }

            sockaddr_un server_addr{};
            server_addr.sun_family = AF_UNIX;
            strcpy(server_addr.sun_path, SOCKET_PATH);

            if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
                throw std::runtime_error("Client connection failed.");
            }

            std::cout << "Client connected to server at " << SOCKET_PATH << std::endl;
        }
    }

    // Send data to the server or client
    bool sendData(const std::vector<uint8_t>& data) override {
        ssize_t bytes_sent = send(socket_fd, data.data(), data.size(), 0);
        return bytes_sent == static_cast<ssize_t>(data.size());
    }

    // Receive data from the server or client
    std::vector<uint8_t> receiveData() override {
        std::vector<uint8_t> buffer(256);  // Buffer for receiving data
        ssize_t bytes_received = recv(socket_fd, buffer.data(), buffer.size(), 0);
        if (bytes_received > 0) {
            buffer.resize(bytes_received);  // Resize buffer to actual received data size
        }
        return buffer;
    }

    // De-initialize (close the socket and clean up)
    void deInit() override {
        if (socket_fd != -1) {
            close(socket_fd);
            socket_fd = -1;
        }

        if (role == Role::SERVER) {
            // Server cleanup: Remove the Unix socket file
            unlink(SOCKET_PATH);
        }
    }

private:
    Role role;
    int socket_fd;
    std::function<void(const std::vector<uint8_t>&, int)> dataCallback;

    // Helper function to accept client connections and spawn threads to handle them
    void acceptClients() {
        int client_id_counter = 1;  // Client ID counter for multiple clients
        while (true) {
            int client_fd = accept(socket_fd, nullptr, nullptr);
            if (client_fd == -1) {
                std::cerr << "Error accepting client connection" << std::endl;
                continue;
            }

            // Spawn a new thread to handle the client
            std::thread client_thread([this, client_fd, &client_id_counter]() {
                this->handleClient(client_fd, client_id_counter++);
            });
            client_thread.detach();  // Detach the thread to handle the client independently
        }
    }

    // Function to handle communication with each client
    void handleClient(int client_fd, int client_id) {
        try {
            SocketCommunication client(Role::CLIENT);
            client.initialize();  // Initialize the client for communication

            std::cout << "Client " << client_id << " connected!" << std::endl;

            // Handle data exchange with the client (e.g., echo)
            while (true) {
                std::vector<uint8_t> data = client.receiveData();
                if (!data.empty() && dataCallback) {
                    // Invoke the registered callback to process the data (e.g., print)
                    dataCallback(data, client_id);
                }
            }

            // Cleanup
            client.deInit();
            close(client_fd);
            std::cout << "Client " << client_id << " disconnected!" << std::endl;

        } catch (const std::exception& ex) {
            std::cerr << "Error handling client " << client_id << ": " << ex.what() << std::endl;
        }
    }
};

#endif /* SOCKETCOMMUNICATION_HPP_ */
