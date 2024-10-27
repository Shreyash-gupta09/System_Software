/*
============================================================================
Name :33a.c
Author :Shreyash Kumar Gupta
Description :Write a program to communicate between two machines using socket.
Date: 20th September,2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0};
    char *hello = "Hello from server";

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Listen on any IP address
    address.sin_port = htons(PORT);        // Convert port to network byte order

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for connections...\n");

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Read the message from the client
    read(new_socket, buffer, BUF_SIZE);
    printf("Message from client: %s\n", buffer);

    // Send a message to the client
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent to client.\n");

    // Close the connection
    close(new_socket);
    close(server_fd);

    return 0;
}

/* OUTPUT
============================================================================
Server is waiting for connections...
Message from client: Hello from client
Hello message sent to client.
============================================================================
*/
