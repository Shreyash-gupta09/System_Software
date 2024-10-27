/*
============================================================================
Name :16.c
Author :Shreyash Kumar Gupta
Description :Write a program to send and receive data from parent to child vice versa. Use two way
             communication.
Date: 15th September,2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parent_to_child[2];
    int child_to_parent[2];
    pid_t pid;
    char parent_msg[] = "Hello from parent!";
    char child_msg[] = "Hello from child!";
    char read_buffer[100];

    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        // Write message to the child
        write(parent_to_child[1], parent_msg, strlen(parent_msg) + 1);

        // Read message from the child
        read(child_to_parent[0], read_buffer, sizeof(read_buffer));
        printf("Parent received: %s\n", read_buffer);

        close(parent_to_child[1]);
        close(child_to_parent[0]);
    }
    else
    {
        // Child process
        close(parent_to_child[1]);
        close(child_to_parent[0]);

        // Read message from the parent
        read(parent_to_child[0], read_buffer, sizeof(read_buffer));
        printf("Child received: %s\n", read_buffer);

        // Write message to the parent
        write(child_to_parent[1], child_msg, strlen(child_msg) + 1);

        close(parent_to_child[0]);
        close(child_to_parent[1]);
    }

    return 0;
}

/* OUTPUT
============================================================================
Child received: Hello from parent!
Parent received: Hello from child!
============================================================================
*/
