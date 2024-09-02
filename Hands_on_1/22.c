/*
============================================================================
Name : 22.c
Author : Shreyash Kumar Gupta
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the
	      parent processes. Check output of the file.
Date: 28th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {

    int fd = open("22_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Failed to open file");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        close(fd);
        exit(1);
    }
      else if (pid == 0) {
        write(fd, "Child process writing\n", 22);
    }
      else {
        write(fd, "Parent process writing\n", 23);
    }

    close(fd);

    return 0;
}




/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./22c
shreyash@shreyash-hp:~/Hands_on_1$ cat 22_file.txt
Parent process writing
Child process writing
shreyash@shreyash-hp:~/Hands_on_1$
============================================================================
*/


