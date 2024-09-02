/*
============================================================================
Name : 26b.c
Author : Shreyash Kumar Gupta
Description : Write a program to execute an executable program.
              a. use some executable program
              b. pass some input to an executable program. (for example execute an executable of $./a.out name).
Date: 29th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"./26ac","Shreyash", NULL};

    printf("Executing 26a.c  program...\n");
    execv(args[0], args);

    // If execv fails, print an error message
    perror("execv failed");
    return 1;
}



/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./26bc
Executing 26a.c  program...
Hello, Shreyash!
============================================================================
*/
