/*
============================================================================
Name : 23.c
Author : Shreyash Kumar Gupta
Description : Write a program to create a Zombie state of the running program.
Date: 28th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if (pid < 0) {

        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {

        printf("Child process is exiting. PID: %d\n", getpid());
        exit(0);
    }
      else {
        printf("Parent process is going to sleep. PID: %d\n", getpid());

        sleep(30); // Sleep for 30 seconds to keep the parent alive


        printf("Parent process is exiting. PID: %d\n", getpid());
    }

    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./23c
Parent process is going to sleep. PID: 5799
Child process is exiting. PID: 5800
Parent process is exiting. PID: 5799


in another terminal check for zombie process

shreyash@shreyash-hp:~/Hands_on_1$ ps aux | grep Z
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
shreyash    5800  0.0  0.0      0     0 pts/1    Z+   00:07   0:00 [23c] <defunct>              z+ denotes zombie process

============================================================================
*/
