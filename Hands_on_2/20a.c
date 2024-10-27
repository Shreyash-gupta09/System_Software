/*
============================================================================
Name :20a.c
Author :Shreyash Kumar Gupta
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 17th September,2024.
============================================================================
*/

//Writer Program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
    char *message = "Hello from the writer!";
    int fd;


    fd = open("FIFO_Program_20", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write the message to the FIFO
    write(fd, message, strlen(message) + 1);

    printf("Message written to FIFO.\n");
    close(fd);
    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./20ac
Message written to FIFO.
============================================================================
*/
