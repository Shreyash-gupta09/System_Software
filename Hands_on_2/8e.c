/*
============================================================================
Name :8e.c
Author :Shreyash Kumar Gupta
Description : Write a separate program using signal system call to catch the following signals.
              (e).SIGALRM (use setitimer system call)
Date: 11th September,2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigalrm(int sig) {
    printf("Caught SIGALRM\n");
}

int main() {
    signal(SIGALRM, handle_sigalrm);  // Set handler for SIGALRM

    struct itimerval timer;
    timer.it_value.tv_sec = 3;  // First alarm after 3 seconds
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;  // No repeating interval
    timer.it_interval.tv_usec = 0;

    printf("Setting setitimer for 3 seconds\n");
    setitimer(ITIMER_REAL, &timer, NULL);

    // Wait for the signal
    pause();

    return 0;
}


/* OUTPUT
===================================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./8ec
Setting setitimer for 3 seconds
Caught SIGALRM
===================================================================================
*/
