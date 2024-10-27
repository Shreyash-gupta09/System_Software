/*
============================================================================
Name :34b_server.c
Author :Shreyash Kumar Gupta
Description :Write a program to create a concurrent server.
                b. pthread_create
Date: 20th September,2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUF_SIZE 1024

// Function that will handle communication with the client
void *handle_client(void *arg) {
    int new_socket = *(int*)arg;
    char buffer[BUF_SIZE] = {0};
    int bytes_read;

    // Read data from the client
    bytes_read = read(new_socket, buffer, BUF_SIZE);
    if (bytes_read < 0) {
        perror("read");
        close(new_socket);
        pthread_exit(NULL);
    }

    printf("Client says: %s\n", buffer);

    // Send a response back to the client
    char *message = "Hello from server!";
    send(new_socket, message, strlen(message), 0);

    // Close the connection
    close(new_socket);
    printf("Client disconnected.\n");

    pthread_exit(NULL);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t thread_id;

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
        // Accept client connections
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, handle_client, (void*)&new_socket) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }

        // Detach the thread so it can clean up after itself
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}

/* OUTPUT
============================================================================
Server is listening on port 8080...
Client says: Hello from client!
Client disconnected.
Client says: Hello from client!
Client disconnected.
============================================================================
*/
