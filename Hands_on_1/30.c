/*
============================================================================
Name : 30.c
Author : Shreyash Kumar Gupta
Description : Write a program to run a script at a specific time using a Daemon process
Date: 29th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int main(int argc, char *argv[])
{
    time_t curr, dead;
    struct tm *deadline;

    time(&curr); // store current time in epoch
    deadline = localtime(&curr);

    // take time from terminal
    deadline->tm_hour = atoi(argv[1]);
    deadline->tm_min = argv[2] == NULL ? 0 : atoi(argv[2]);
    deadline->tm_sec = argv[3] == NULL ? 0 : atoi(argv[3]);

    dead = mktime(deadline); // convert time to epoch

    int cid = fork();
    if (cid == 0)
    {
        // as parent is executed so chile becomes orphan using sessid it will become demon process;
        setsid();
        do
        {
            time(&curr); // get curr time
        } while (difftime(dead, curr) > 0);
        // run untill current time becomes deadline
        system("/home/shreyash/Hands_on_1/script.sh");            //path of your script
    }
    else
    {
        exit(0);
    }
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./30c 20 38
shreyash@shreyash-hp:~/Hands_on_1$ Hello this is a sample script
============================================================================
*/
