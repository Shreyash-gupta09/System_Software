/*
============================================================================
Name : 26a.c
Author : Shreyash Kumar Gupta
Description : Write a program to execute an executable program.
	      a. use some executable program
              b. pass some input to an executable program. (for example execute an executable of $./a.out name).
Date: 29th Aug, 2024.
============================================================================
*/

//simple program to greet.

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }
    printf("Hello, %s!\n", argv[1]);
    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./26ac Shreyash
Hello, Shreyash!
============================================================================
*/
