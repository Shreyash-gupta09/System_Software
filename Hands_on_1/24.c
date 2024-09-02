/*
============================================================================
Name : 24.c
Author : Shreyash Kumar Gupta
Description : Write a program to create an orphan process.
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
    }

    else if(pid!=0){
        printf("Parent process exiting. PID: %d\n", getpid());
        exit(0);
    }
    else  {
        sleep(2);
        printf("Child process, PID: %d, Parent PID: %d\n", getpid(), getppid());
    }

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./24c

Parent process exiting. PID: 8045

shreyash@shreyash-hp:~/Hands_on_1$ Child process, PID: 8046, Parent PID: 2031

============================================================================
*/
