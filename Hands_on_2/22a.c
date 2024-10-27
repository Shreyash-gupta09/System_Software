/*
============================================================================
Name :22a.c
Author :Shreyash Kumar Gupta
Description :Write a program to wait for data to be written into FIFO within 10 seconds, use select
	     system call with FIFO.
Date: 17th September,2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>


int main() {
    int fd;
    char buffer[100];
    fd_set readfds;
    struct timeval timeout;

    // Open the FIFO for reading (non-blocking mode)
    fd = open("FIFO_22", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Set up the file descriptor set
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    // Set the timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Use select to wait for data
    int retval = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select");
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        printf("Timeout: No data within %d seconds.\n", 10);
    } else {
        // If data is available, read it
        int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';  // Null-terminate the string
            printf("Received: %s\n", buffer);
        } else {
            printf("No data read from FIFO.\n");
        }
    }


    close(fd);
    return 0;
}


/* OUTPUT
============================================================================
IF NO DATA IS PROVIDED WITHIN 10 SECONDS
shreyash@shreyash-hp:~/Hands_on_2$ ./22ac
Timeout: No data within 10 seconds.

IF DATA IS PROVIDED WITHIN 10 SECONDS
shreyash@shreyash-hp:~/Hands_on_2$ ./22ac
Received: Hello from the writer!
============================================================================
*/
