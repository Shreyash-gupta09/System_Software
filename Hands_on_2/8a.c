/*
============================================================================
Name :8a.c
Author :Shreyash Kumar Gupta
Description : Write a separate program using signal system call to catch the following signals.
	      (a). SIGSEGV
Date: 11th September,2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV (Segmentation fault)\n");
    exit(1);  // Exit after handling the signal
}

int main() {
    signal(SIGSEGV, handle_sigsegv);

   // Example of causing SIGSEGV by dereferencing a NULL pointer
    int *ptr = NULL;
    *ptr = 10;  // This will cause a segmentation fault
    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./8ac
Caught SIGSEGV (Segmentation fault)
============================================================================
*/

