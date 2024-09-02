/*
============================================================================
Name : 29.c
Author : Shreyash Kumar Gupta
Description : Write a program to get scheduling policy and modify the scheduling policy
	      (SCHED_FIFO,SCHED_RR).
Date: 29th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void print_policy(int policy) {
    if (policy == SCHED_FIFO)
        printf("Current Scheduling Policy: SCHED_FIFO\n");
    else if (policy == SCHED_RR)
        printf("Current Scheduling Policy: SCHED_RR\n");
    else if (policy == SCHED_OTHER)
        printf("Current Scheduling Policy: SCHED_OTHER\n");
    else
        printf("Current Scheduling Policy: UNKNOWN\n");
}

int main() {
    pid_t pid;
    int policy;
    struct sched_param param;

    pid = getpid();

    policy = sched_getscheduler(pid);

    if (policy == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }

    print_policy(policy);

    if (sched_getparam(pid, &param) == -1) {
        perror("sched_getparam");
        exit(EXIT_FAILURE);
    }
    printf("Current Priority: %d\n", param.sched_priority);

    param.sched_priority = 10;
    if (sched_setscheduler(pid, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }

    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }
    print_policy(policy);
    printf("New Priority: %d\n", param.sched_priority);

    param.sched_priority = 15;
    if (sched_setscheduler(pid, SCHED_RR, &param) == -1) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }

    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }
    print_policy(policy);
    printf("New Priority: %d\n", param.sched_priority);

    return 0;
}


/* OUTPUT (To change policy you must be logged in as a root user)
============================================================================
root@shreyash-hp:/home/shreyash/Hands_on_1# ./29c
Current Scheduling Policy: SCHED_OTHER
Current Priority: 0
Current Scheduling Policy: SCHED_FIFO
New Priority: 10
Current Scheduling Policy: SCHED_RR
New Priority: 15

============================================================================
*/

