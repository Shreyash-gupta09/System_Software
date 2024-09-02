/*
============================================================================
Name : 21.c
Author : Shreyash Kumar Gupta
Description : Write a program, call fork and print the parent and child process id.
Date: 28th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("\nThis is the child process.\n");
        printf("Child PID: %d\n", getpid());                                                              //parent and child runs concurrently therefore output may vary
        printf("Parent PID of child: %d\n", getppid());
    } else {
        // Parent process
        printf("\nThis is the parent process.\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }

    return 0;
}

/* OUTPUT
==================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./21c

This is the parent process.
Parent PID: 7218
Child PID: 7219

This is the child process.
Child PID: 7219
Parent PID of child: 7218
=================================================
*/
