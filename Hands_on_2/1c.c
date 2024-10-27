/*
============================================================================
Name : 1c.c
Author : Shreyash Kumar Gupta
Description : Write a program to set a interval timer in 10sec and
                10micro second
		c. ITIMER_PROF
Date: 3rd September,2024.
============================================================================
*/
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void timer_handler(int signum) {
    printf("ITIMER_PROF: Timer expired!\n");
}

int main() {
    struct itimerval timer;
    signal(SIGPROF, timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_PROF, &timer, NULL);

    while (1);
    return 0;
}
/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./1cc
ITIMER_PROF: Timer expired!
ITIMER_PROF: Timer expired!
ITIMER_PROF: Timer expired!
============================================================================
*/
