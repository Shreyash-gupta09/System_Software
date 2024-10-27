/*
============================================================================
Name :8c.c
Author :Shreyash Kumar Gupta
Description : Write a separate program using signal system call to catch the following signals.
              (c)SIGFPE
Date: 11th September,2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigfpe(int sig) {
    printf("Caught SIGFPE (Floating-point exception)\n");
    exit(1);
}

int main() {
    signal(SIGFPE, handle_sigfpe);  // Set handler for SIGFPE

    int x = 1 / 0;        // Trigger SIGFPE by division by zero
    return 0;
}
/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./8cc
Caught SIGFPE (Floating-point exception)
============================================================================
*/
