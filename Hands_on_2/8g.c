/*
============================================================================
Name :8e.c
Author :Shreyash Kumar Gupta
Description : Write a separate program using signal system call to catch the following signals.
	      (g)SIGPROF (use setitimer system call)
Date: 11th September,2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
void handle_sigprof(int sig) {
    printf("Caught SIGPROF\n");
    exit(1);
}

int main() {
    signal(SIGPROF, handle_sigprof);  // Set handler for SIGPROF

    struct itimerval timer;
    timer.it_value.tv_sec = 4;  // First alarm after 4 seconds
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;  // No repeating interval
    timer.it_interval.tv_usec = 0;

    printf("Setting setitimer for 4 seconds (SIGPROF)\n");
    setitimer(ITIMER_PROF, &timer, NULL);

    // Wait for the signal
    while(1);

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./8gc
Setting setitimer for 4 seconds (SIGPROF)
Caught SIGPROF
============================================================================
*/
