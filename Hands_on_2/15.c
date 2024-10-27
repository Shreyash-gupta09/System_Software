/*
============================================================================
Name :15.c
Author :Shreyash Kumar Gupta
Description :Write a simple program to send some data from parent to the child process.
Date: 15th September,2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

    if (pipe(fd) == -1) {
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
        close(fd[0]);

        write(fd[1], write_msg, strlen(write_msg) + 1);  // +1 for null terminator

        close(fd[1]);
    }
    else
    {    //child process

        close(fd[1]);

        read(fd[0], read_msg, sizeof(read_msg));

        printf("Child received: %s\n", read_msg);

        close(fd[0]);
    }

    return 0;
}

/* OUTPUT
============================================================================
Child received: Hello from parent!
============================================================================
*/
