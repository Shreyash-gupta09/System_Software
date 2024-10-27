/*
============================================================================
Name :23.c
Author :Shreyash Kumar Gupta
Description :Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 17th September,2024.
============================================================================
*/
#include<stdio.h>
#include <unistd.h>

int main() {
    long PIPE_BUF, OPEN_MAX;

    PIPE_BUF = pathconf(".", _PC_PIPE_BUF);
    OPEN_MAX = sysconf(_SC_OPEN_MAX);

    printf("Pipe_buf = %ld\t OPEN_MAX = %ld\n", PIPE_BUF, OPEN_MAX);
return 0;
}



/* OUTPUT
============================================================================
Pipe_buf = 4096  OPEN_MAX = 1048576
============================================================================
*/
