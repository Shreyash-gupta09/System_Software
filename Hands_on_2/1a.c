/*
============================================================================
Name : 1a.c
Author : Shreyash Kumar Gupta
Description : Write a program to set a interval timer in 10sec and
		10micro second
		a. ITIMER_REAL
Date: 3rd September,2024.
============================================================================
*/
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void timer_handler(int signum) {
    printf("ITIMER_REAL: Timer expired!\n");
}

int main() {
    struct itimerval timer;
    signal(SIGALRM, timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_REAL, &timer, NULL);

    // Infinite loop to keep the program running
    while (1);
    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./1ac
ITIMER_REAL: Timer expired!
ITIMER_REAL: Timer expired!
ITIMER_REAL: Timer expired!                       program continues to print after every 10s and 10usec
============================================================================
*/

