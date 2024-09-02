/*
============================================================================
Name : 11.c
Author : Shreyash Kumar Gupta
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the
              descriptors and check whether the file is updated properly or not.
               a. use dup
               b. use dup2
               c. use fcntl

Date: 25th Aug, 2024.
============================================================================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
    int fd = open("11_file", O_WRONLY | O_APPEND | O_CREAT, 0600);

    int fd_dup = dup(fd);              // Duplicate using dup
    int fd_dup2 = dup2(fd, fd_dup + 1); // Duplicate using dup2
    int fd_fcntl = fcntl(fd, F_DUPFD, fd_dup2 + 1); // Duplicate using fcntl

    write(fd, "message using original fd\n",26 );        // Write using original fd
    write(fd_dup, "message using first duplicate fd\n", 33);          // Write using dup
    write(fd_dup2, "message using second duplicate fd\n",34);        // Write using dup2
    write(fd_fcntl, "message using fctnl fd\n",23);      // Write using fcntl

    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);

    return 0;
}


/* OUTPUT
=================================================
shreyash@shreyash-hp:~/Hands_on_1$ cat 11_file
message using original fd
message using first duplicate fd
message using second duplicate fd
message using fctnl fd
=================================================
*/
