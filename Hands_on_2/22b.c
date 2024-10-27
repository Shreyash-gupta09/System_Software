/*
============================================================================
Name :22b.c
Author :Shreyash Kumar Gupta
Description :Write a program to wait for data to be written into FIFO within 10 seconds, use select
	     system call with FIFO.
Date: 17th September,2024.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main() {
    int fd;
    char *message = "Hello from the writer!";

    fd = open("FIFO_22", O_WRONLY);

    // Write the message to the FIFO
    write(fd, message, strlen(message));
    printf("Data Sent\n");
    close(fd);
    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./22bc
Data Sent
============================================================================
*/
