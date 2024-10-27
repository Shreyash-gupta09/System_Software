/*
============================================================================
Name :8b.c
Author :Shreyash Kumar Gupta
Description : Write a separate program using signal system call to catch the following signals.
	      (b). SIGINT
Date: 11th September,2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void handle_sigint(int sig) {
    printf("Caught SIGINT (Interrupt from keyboard)\n");
    exit(1);
}

int main() {
    signal(SIGINT, handle_sigint);  // Set handler for SIGINT

    printf("Press Ctrl+C to trigger SIGINT\n");

    // Wait for signal
    while(1) {
    }

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./8bc
Press Ctrl+C to trigger SIGINT
^CCaught SIGINT (Interrupt from keyboard)
============================================================================
*/
