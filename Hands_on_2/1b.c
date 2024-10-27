/*
============================================================================
Name : 1b.c
Author : Shreyash Kumar Gupta
Description : Write a program to set a interval timer in 10sec and
                10micro second
		b.ITIMER_VIRTUAL
Date: 3rd September,2024.
============================================================================
*/
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void timer_handler(int signum) {
    printf("ITIMER_VIRTUAL: Timer expired!\n");
}

int main() {
    struct itimerval timer;
    signal(SIGVTALRM, timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    while (1);
    return 0;
}
/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./1bc
ITIMER_VIRTUAL: Timer expired!
ITIMER_VIRTUAL: Timer expired!
ITIMER_VIRTUAL: Timer expired!
============================================================================
*/
