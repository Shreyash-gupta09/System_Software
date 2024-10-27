/*
============================================================================
Name :12.c
Author :Shreyash Kumar Gupta
Description :Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
		the parent process from the child process.
Date: 15th September,2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // This is the child process
        printf("Child process (PID: %d) created.\n", getpid());

        pid_t parent_pid = getppid();
        printf("Parent PID before kill: %d\n", parent_pid);

        // Wait for a bit to ensure the parent process is running
        sleep(2);

        if (kill(parent_pid, SIGKILL) == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }

        printf("Sent SIGKILL to parent process (PID: %d).\n", parent_pid);

        // Wait to observe the orphan process
        sleep(10);

        parent_pid = getppid();
        printf("Parent PID after kill: %d\n", parent_pid);

        printf("Child process (PID: %d) exiting.\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        printf("Parent process (PID: %d) created.\n", getpid());

        wait(NULL);

        printf("Parent process exiting.\n");
    }

    return 0;
}

/* OUTPUT
============================================================================
Parent process (PID: 24374) created.
Child process (PID: 24375) created.
Parent PID before kill: 24374
Sent SIGKILL to parent process (PID: 24374).
Killed
Parent PID after kill: 2031
Child process (PID: 24375) exiting.
============================================================================
*/
