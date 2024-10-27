/*
============================================================================
Name :17a.c
Author :Shreyash Kumar Gupta
Description :. Write a program to execute ls -l | wc.
	       a. use dup
Date: 17th September,2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>

void main(){
    int pipefd[2];
    pid_t cid;

    if(pipe(pipefd)==-1){
        printf("ERROR");
    }
    else
    {
        cid=fork();
        if(cid==0){
            //closing standard output
            close(0);
            dup(pipefd[0]);
            close(pipefd[1]);
            execl("/usr/bin/wc", "wc", NULL);
        }
	else
	{
            close(1);
            dup(pipefd[1]);
            close(pipefd[0]);

            execl("/usr/bin/ls", "ls -l", "-l", NULL);
        }
    }
}
/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./17ac
     62     551    3336
============================================================================
*/
