/*
============================================================================
Name : 28.c
Author : Shreyash Kumar Gupta
Description : Write a program to get maximum and minimum real time priority.
Date: 29th Aug, 2024.
============================================================================
*/


#include <stdio.h>
#include <sched.h>

int main() {

    printf("\nSCHED_FIFO:\n");
    printf("Max priority: %d\n", sched_get_priority_max(SCHED_FIFO));
    printf("Min priority: %d\n", sched_get_priority_min(SCHED_FIFO));


    printf("\nSCHED_RR:\n");
    printf("Max priority: %d\n", sched_get_priority_max(SCHED_RR));
    printf("Min priority: %d\n", sched_get_priority_min(SCHED_RR));

    printf("\nSCHED_OTHER:\n");
    printf("Max priority: %d\n", sched_get_priority_max(SCHED_OTHER));
    printf("Min priority: %d\n", sched_get_priority_min(SCHED_OTHER));
    return 0;
}


/* OUTPUT
============================================================================
SCHED_FIFO:
Max priority: 99
Min priority: 1

SCHED_RR:
Max priority: 99
Min priority: 1

SCHED_OTHER:
Max priority: 0
Min priority: 0

============================================================================
*/
