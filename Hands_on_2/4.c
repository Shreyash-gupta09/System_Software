/*
============================================================================
Name : 4.c
Author : Shreyash Kumar Gupta
Description : Write a program to measure how much time is taken to execute 100 getppid ( )
	      system call. Use time stamp counter.
Date: 3rd September,2024.
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

    for(int i=1;i<=100;i++){
         int ppid=getppid();
    }

    end = rdtsc();

    printf("Time to execute 100 getppid() calls : %llu\n", end - start);
}

/*OUTPUT
==============================================
shreyash@shreyash-hp:~/Hands_on_2$ ./4c
Time to execute 100 getppid() calls : 77220
=============================================
*/
