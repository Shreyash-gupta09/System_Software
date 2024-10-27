/*
============================================================================
Name :8f.c
Author :Shreyash Kumar Gupta
Description : Write a separate program using signal system call to catch the following signals.
              (f).SIGVTALRM (use setitimer system call)
Date: 11th September,2024.
============================================================================
*/

#include <stdio.h>
#include<stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigvtalrm(int sig) {
    printf("Caught SIGVTALRM\n");
    exit(1);
}

int main() {
    signal(SIGVTALRM, handle_sigvtalrm);  // Set handler for SIGVTALRM

    struct itimerval timer;
    timer.it_value.tv_sec = 2;  // First alarm after 2 seconds
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;  // No repeating interval
    timer.it_interval.tv_usec = 0;

    printf("Setting setitimer for 2 seconds (SIGVTALRM)\n");
    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    // Wait for the signal
	while(1);
    return 0;
}

/* OUTPUT
==============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./8fc
Setting setitimer for 2 seconds (SIGVTALRM)
Caught SIGVTALRM
==============================================================================
*/
