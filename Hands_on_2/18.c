/*
============================================================================
Name :18.c
Author :Shreyash Kumar Gupta
Description :Write a program to find out total number of directories on the pwd.
	     execute ls -l | grep ^d | wc ? Use only dup2.
Date: 17th September,2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h> 
int main() {
    int pipefd1[2], pipefd2[2];
    pid_t pid1, pid2;

    // Create the first pipe for ls -l to grep
    if (pipe(pipefd1) == -1) {
        perror("Pipe1 failed");
        exit(EXIT_FAILURE);
    }

    // Create the second pipe for grep to wc
    if (pipe(pipefd2) == -1) {
        perror("Pipe2 failed");
        exit(EXIT_FAILURE);
    }

    // Fork the first child for ls -l
    if ((pid1 = fork()) == -1) {
        perror("Fork1 failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process for ls -l
        close(pipefd1[0]); // Close unused read end of pipe1
        dup2(pipefd1[1], STDOUT_FILENO); // Redirect stdout to pipe1
        close(pipefd1[1]); // Close original write end

        execlp("ls", "ls", "-l", NULL); // Execute ls -l
        perror("execlp ls failed");
        exit(EXIT_FAILURE);
    }

    // Fork the second child for grep
    if ((pid2 = fork()) == -1) {
        perror("Fork2 failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process for grep
        close(pipefd1[1]); // Close unused write end of pipe1
        dup2(pipefd1[0], STDIN_FILENO); // Redirect stdin to read from pipe1
        close(pipefd1[0]); // Close original read end

        close(pipefd2[0]); // Close unused read end of pipe2
        dup2(pipefd2[1], STDOUT_FILENO); // Redirect stdout to pipe2
        close(pipefd2[1]); // Close original write end

        execlp("grep", "grep", "^d", NULL); // Execute grep ^d
        perror("execlp grep failed");
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[1]);

    // Wait for the second child to finish
    wait(NULL);

    // Execute wc to count lines
    dup2(pipefd2[0], STDIN_FILENO); // Redirect stdin to read from pipe2
    close(pipefd2[0]); // Close original read end

    execlp("wc", "wc", "-l", NULL); // Execute wc -l to count directories
    perror("execlp wc failed");
    exit(EXIT_FAILURE);

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./18c
0
============================================================================
*/
