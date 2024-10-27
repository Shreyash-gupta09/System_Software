/*
============================================================================
Name :20b.c
Author :Shreyash Kumar Gupta
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 17th September,2024.
============================================================================
*/

//Reader Program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
    char buffer[100];
    int fd;

    fd = open("FIFO_Program_20", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read the message from the FIFO
    read(fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);

    close(fd);

    return 0;
}
/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./20bc
Received: Hello from the writer!
============================================================================
*/
