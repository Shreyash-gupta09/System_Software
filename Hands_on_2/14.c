/*
============================================================================
Name :14.c
Author :Shreyash Kumar Gupta
Description :Write a simple program to create a pipe, write to the pipe, read from pipe and display on
	     the monitor.
Date: 15th September,2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];  // fd[0] for reading, fd[1] for writing
    char write_msg[] = "Hello from the pipe!";
    char read_msg[100];

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    write(fd[1], write_msg, strlen(write_msg) + 1);  // +1 to include the null terminator

    read(fd[0], read_msg, sizeof(read_msg));

    printf("Read from pipe: %s\n", read_msg);

    close(fd[0]);
    close(fd[1]);

    return 0;
}

/* OUTPUT
============================================================================
Read from pipe: Hello from the pipe!
============================================================================
*/
