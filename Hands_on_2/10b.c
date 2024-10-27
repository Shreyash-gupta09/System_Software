/*
============================================================================
Name :10b.c
Author :Shreyash Kumar Gupta
Description :Write a separate program using sigaction system call to catch the following signals.
                b. SIGINT
Date: 15th September,2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void handle_sigint(int sig, siginfo_t *info, void *context) {
    printf("Caught SIGINT (Interrupt Signal)\n");
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = handle_sigint;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C to trigger SIGINT\n");

    while (1);

    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./10bc
Press Ctrl+C to trigger SIGINT
^CCaught SIGINT (Interrupt Signal)
============================================================================
*/
