/*
============================================================================
Name : 20.c
Author : Shreyash Kumar Gupta
Description : Find out the priority of your running program. Modify the priority with nice command.
Date: 27th Aug, 2024.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
printf("Sample program of which priority is going to be changed by nice command\n");

sleep(120);
}

/*OUTPUT
================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ps -o pid,ni,comm -p 7146
    PID  NI COMMAND
   7146   0 20c

shreyash@shreyash-hp:~/Hands_on_1$ renice 5 -p 7146
7146 (process ID) old priority 0, new priority 5

shreyash@shreyash-hp:~/Hands_on_1$ ps -o pid,ni,comm -p 7146
    PID  NI COMMAND
   7146   5 20c

=================================================================
*/

