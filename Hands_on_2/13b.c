/*
============================================================================
Name :13b.c
Author :Shreyash Kumar Gupta
Description :Write two programs: first program is waiting to catch SIGSTOP signal, the second program
             will send the signal (using kill system call). Find out whether the first program is able to catch
             the signal or not
Date: 15th September,2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("Enter the PID of Program 1: ");
    scanf("%d", &pid);

    printf("Sending SIGSTOP to PID %d\n", pid);
    if (kill(pid, SIGSTOP) == -1) {
        perror("Error sending SIGSTOP");
    }

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./13bc
Enter the PID of Program 1: 8804
Sending SIGSTOP to PID 8804
============================================================================
*/
