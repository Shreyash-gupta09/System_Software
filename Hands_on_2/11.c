/*
============================================================================
Name :11.c
Author :Shreyash Kumar Gupta
Description :Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
	     use sigaction system call.
Date: 15th September,2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;    // Set the handler to ignore the signal
    sigemptyset(&sa.sa_mask);   // No additional signals will be blocked
    sa.sa_flags = 0;            // No special flags
    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT is now ignored. Try pressing Ctrl+C...\n");
    sleep(5);

    sa.sa_handler = SIG_DFL;   // Set the handler to the default action
    sigaction(SIGINT, &sa, NULL); // Reset SIGINT to its default action

    printf("\nSIGINT default action restored. Try pressing Ctrl+C again...\n");
    sleep(5);

    printf("\nProgram is exiting");
    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./11c
SIGINT is now ignored. Try pressing Ctrl+C...
^C^C^C
SIGINT default action restored. Try pressing Ctrl+C again...
^C
shreyash@shreyash-hp:~/Hands_on_2$
============================================================================
*/

