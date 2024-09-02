/*
============================================================================
Name : 19.c
Author : Shreyash Kumar Gupta
Description : Write a program to find out time taken to execute getpid system call. Use time stamp counter.
Date: 27th Aug, 2024.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

// using time stamp counter
unsigned long long rdtsc()
{
    unsigned long long dst;
    __asm__ __volatile__("rdtsc": "=A"(dst));
    return dst;
}

void main()
{
    long long int start, end;

    start = rdtsc();

    printf("Process id: %d\n", getpid());

    end = rdtsc();

    printf("Difference is : %llu\n", end - start);
}


/*OUTPUT
==============================================
shreyash@shreyash-hp:~/Hands_on_1$ ./19c
Process id: 6980
Difference is : 119922
=============================================
*/
