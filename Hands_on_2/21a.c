/*
============================================================================
Name :21a.c
Author :Shreyash Kumar Gupta
Description :Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 17th September,2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
    char buffer[100];
    int fd1, fd2;


    fd1 = open("FIFO1", O_WRONLY);
    fd2 = open("FIFO2", O_RDONLY);

    // Send message to the second communicator
    char *message1 = "Hello from communicator 1!";
    write(fd1, message1, strlen(message1) + 1);

    // Read response from the second communicator
    read(fd2, buffer, sizeof(buffer));
    printf("Communicator 1 received: %s\n", buffer);

    // Close FIFOs
    close(fd1);
    close(fd2);

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./21ac
Communicator 1 received: Hello from communicator 2!
============================================================================
*/
