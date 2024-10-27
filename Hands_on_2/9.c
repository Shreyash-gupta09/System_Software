/*
============================================================================
Name :9.c
Author :Shreyash Kumar Gupta
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
		signal - Use signal system call.
Date: 11th September,2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ignore_sigint(int sig) {
    printf("\nSIGINT signal is currently being ignored.\n");
}

int main() {
    signal(SIGINT, SIG_IGN);
    printf("\nSIGINT is now being ignored. Press Ctrl+C to test.\n");

    // Wait for 5 seconds to demonstrate ignoring
    sleep(10);

    signal(SIGINT, SIG_DFL);
    printf("\nSIGINT has been reset to default action. Press Ctrl+C to test.\n");

    // Wait for another 5 seconds to demonstrate the default action
    sleep(10);

    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./9c

SIGINT is now being ignored. Press Ctrl+C to test.
^C^C^C
SIGINT has been reset to default action. Press Ctrl+C to test.
^C
============================================================================
*/
