/*
============================================================================
Name :17b.c
Author :Shreyash Kumar Gupta
Description :. Write a program to execute ls -l | wc.
               b. use dup2
Date: 17th September,2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main()
{
    int pipefd[2];
    pid_t cid;

    if (pipe(pipefd )== -1)
    {
        printf("ERROR");
    }
    else
    {
        cid = fork();
        if (cid == 0)
        {
            // closing standard output
            close(0);
            dup2(pipefd[0], 0);
            close(pipefd[1]);
            execl("/usr/bin/wc", "wc", NULL);
        }
        else
        {
            close(1);
            dup2(pipefd[1], 1);
            close(pipefd[0]);

            execl("/usr/bin/ls", "ls -l", "-l", NULL);
        }
    }
}
/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./17bc
     61     542    3281
============================================================================
*/
