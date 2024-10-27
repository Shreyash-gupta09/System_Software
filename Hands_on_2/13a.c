/*
============================================================================
Name :13a.c
Author :Shreyash Kumar Gupta
Description :Write two programs: first program is waiting to catch SIGSTOP signal, the second program
	     will send the signal (using kill system call). Find out whether the first program is able to catch
             the signal or not
Date: 15th September,2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signo) {
    if (signo == SIGSTOP) {
        printf("Received SIGSTOP\n");
    }
}

int main() {
    printf("Program 1 (PID: %d) waiting for SIGSTOP...\n", getpid());

    signal(SIGSTOP, sig_handler);


    while (1) {
        sleep(1);
    }

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./13ac
Program 1 (PID: 8804) waiting for SIGSTOP...

[1]+  Stopped                 ./13ac

============================================================================
*/
