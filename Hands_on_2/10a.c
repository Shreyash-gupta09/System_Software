/*
============================================================================
Name :10a.c
Author :Shreyash Kumar Gupta
Description :Write a separate program using sigaction system call to catch the following signals.
		a. SIGSEGV
Date: 15th September,2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigsegv(int sig, siginfo_t *info, void *context) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(1);  // Terminate the program after handling
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = handle_sigsegv;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);

    int *ptr = NULL;
    *ptr = 10;

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./10ac
Caught SIGSEGV (Segmentation Fault)
============================================================================
*/
