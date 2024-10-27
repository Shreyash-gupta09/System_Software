/*
============================================================================
Name :33b.c
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
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    // Define server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert server IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {  // Replace SERVER_IP_ADDRESS
        printf("\nInvalid address/Address not supported\n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection failed\n");
        return -1;
    }

    // Send a message to the server
    char *message = "Hello from client";
    send(sock, message, strlen(message), 0);
    printf("Message sent to server: %s\n", message);

    // Read the response from the server
    read(sock, buffer, BUF_SIZE);
    printf("Message from server: %s\n", buffer);

    close(sock);

    return 0;
}
/* OUTPUT
============================================================================
Message sent to server: Hello from client
Message from server: Hello from server

============================================================================
*/
