/*
============================================================================
Name :34a_server.c
Author :Shreyash Kumar Gupta
Description :Write a program to create a concurrent server.
		a. use fork
Date: 20th September,2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

void handle_client(int new_socket) {
    char buffer[BUF_SIZE] = {0};
    int bytes_read;

    // Read data from the client
    bytes_read = read(new_socket, buffer, BUF_SIZE);
    if (bytes_read < 0) {
        perror("read");
        close(new_socket);
        exit(EXIT_FAILURE);
    }

    printf("Client says: %s\n", buffer);

    // Send response back to the client
    char *message = "Hello from server!";
    send(new_socket, message, strlen(message), 0);

    // Close the connection
    close(new_socket);
    printf("Client disconnected.\n");
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Define address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Fork a new process for each client
        pid_t pid = fork();
        if (pid == 0) {  // Child process
            close(server_fd);  // Close server socket in child
            handle_client(new_socket);
            exit(0);  // Exit child process after handling client
        } else if (pid > 0) {  // Parent process
            close(new_socket);  // Close client socket in parent
        } else {
            perror("fork");
        }
    }

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./34aa
Server is listening on port 8080...
Client says: Hello from client!
Client disconnected.
Client says: Hello from client!
Client disconnected.
============================================================================
*/
