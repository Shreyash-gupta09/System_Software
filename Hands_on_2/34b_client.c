/*
============================================================================
Name :34b_client.c
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

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    // Define server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Send a message to the server
    char *message = "Hello from client!";
    send(sock, message, strlen(message), 0);
    printf("Message sent to server: %s\n", message);

    // Read server response
    int bytes_read = read(sock, buffer, BUF_SIZE);
    printf("Message from server: %s\n", buffer);

    // Close the socket
    close(sock);

    return 0;
}
/* OUTPUT
============================================================================
Message sent to server: Hello from client!
Message from server: Hello from server!
============================================================================
*/
