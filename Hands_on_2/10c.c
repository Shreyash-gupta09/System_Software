/*
============================================================================
Name :10c.c
Author :Shreyash Kumar Gupta
Description :Write a separate program using sigaction system call to catch the following signals.
                c. SIGFPE
Date: 15th September,2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigfpe(int sig, siginfo_t *info, void *context) {
    printf("Caught SIGFPE (Floating Point Exception)\n");
    exit(1);  // Terminate the program after handling
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = handle_sigfpe;
    sa.sa_flags = SA_SIGINFO;

    // Set up the sigaction for SIGFPE
    sigaction(SIGFPE, &sa, NULL);

    // Cause a floating point exception by dividing by zero
    int a = 5 / 0;

    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./10cc
Caught SIGFPE (Floating Point Exception)
============================================================================
*/
