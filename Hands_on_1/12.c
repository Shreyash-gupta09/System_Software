/*
============================================================================
Name : 12.c
Author : Shreyash Kumar Gupta
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 26th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("12_file",O_RDONLY);  // Open file in read-only mode

    int flags = fcntl(fd, F_GETFL);  // Get file flags

    if (flags & O_WRONLY)						//or u can use int access_mode= flags & O_ACCMODE;
	printf("File opened in Write-only mode\n");			// and then compare for values of access mode
    else if (flags & O_RDWR)
        printf("File opened in Read-write mode\n");
    else
        printf("File opened in Read-only mode\n");                                //bitwise comparison between flags variable and standard access modes

    close(fd);  // Close the file
    return 0;
}



/* OUTPUT
===========================================
shreyash@shreyash-hp:~/Hands_on_1$ ./12c
File opened in Read-only mode
===========================================
*/
