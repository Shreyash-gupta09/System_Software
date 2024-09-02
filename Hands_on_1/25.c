/*
============================================================================
Name : 25.c
Author : Shreyash Kumar Gupta
Description : Write a program to create three child processes. The parent should wait for a particular child (use
	      waitpid system call).
Date: 29th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 == 0) {
	printf("\n1st child running wiht pid : %d\n",getpid());
        sleep(2);
	printf("\n1st child exiting\n");
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
	printf("\n2nd child running wiht pid : %d\n",getpid());
        sleep(4);
	printf("\n2nd child exiting\n");
        exit(0);
    }

    pid3 = fork();
    if (pid3 == 0) {
	printf("\n3rd child running wiht pid : %d\n",getpid());
        sleep(6);
	printf("\n3rd child exiting\n");

        exit(0);
    }

    int status;
    waitpid(pid2, &status, 0);

    printf("\nSecond child finished with status %d.. parent exiting\n",status);
    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ gcc 25.c -o 25c
shreyash@shreyash-hp:~/Hands_on_1$ ./25c

1st child running wiht pid : 5668

2nd child running wiht pid : 5669

3rd child running wiht pid : 5670

1st child exiting

2nd child exiting

Second child finished with status 0.. parent exiting

shreyash@shreyash-hp:~/Hands_on_1$

3rd child exiting


============================================================================
*/
