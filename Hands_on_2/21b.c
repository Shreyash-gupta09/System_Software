/*
============================================================================
Name :21b.c
Author :Shreyash Kumar Gupta
Description :Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 15th September,2024.
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

    fd1 = open("FIFO1", O_RDONLY);
    fd2 = open("FIFO2", O_WRONLY);

    read(fd1, buffer, sizeof(buffer));
    printf("Communicator 2 received: %s\n", buffer);

    char *message2 = "Hello from communicator 2!";
    write(fd2, message2, strlen(message2) + 1);

    close(fd1);
    close(fd2);
    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./21bc
Communicator 2 received: Hello from communicator 1!
============================================================================
*/
