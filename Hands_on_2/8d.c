/*
============================================================================
Name :8d.c
Author :Shreyash Kumar Gupta
Description : Write a separate program using signal system call to catch the following signals.
              (d)SIGALRM (use alarm system call)
Date: 11th September,2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigalrm(int sig) {
    printf("Caught SIGALRM (Alarm signal)\n");
}

int main() {
    signal(SIGALRM, handle_sigalrm);

    printf("Setting alarm for 2 seconds\n");
    alarm(2);  // Set alarm for 2 seconds

    pause();

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./8dc
Setting alarm for 2 seconds
Caught SIGALRM (Alarm signal)
============================================================================
*/
