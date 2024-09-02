/*
============================================================================
Name : 14.c
Author : Shreyash Kumar Gupta
Description : Write a program to find the type of a file.
              a. Input should be taken from command line.
              b. program should be able to identify any type of a file.
Date: 26th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Entry should be like: %s <file_path>\n", argv[0]);
        return 1;
    }
    struct stat fileStat;

    if (stat(argv[1], &fileStat) < 0) {
        perror("Failed to get file status");
        return 1;
    }

    if (S_ISREG(fileStat.st_mode))
        printf("%s is a regular file\n", argv[1]);
    else if (S_ISDIR(fileStat.st_mode))
        printf("%s is a directory\n", argv[1]);
    else if (S_ISCHR(fileStat.st_mode))
        printf("%s is a character device\n", argv[1]);
    else if (S_ISBLK(fileStat.st_mode))
        printf("%s is a block device\n", argv[1]);
    else if (S_ISFIFO(fileStat.st_mode))
        printf("%s is a FIFO/pipe\n", argv[1]);
    else if (S_ISLNK(fileStat.st_mode))
        printf("%s is a symbolic link\n", argv[1]);
    else if (S_ISSOCK(fileStat.st_mode))
        printf("%s is a socket\n", argv[1]);
    else
        printf("%s is of an unknown type\n", argv[1]);

    return 0;
}

/*
==================================================
SAMPLE OUTPUT :
shreyash@shreyash-hp:~/Hands_on_1$ ./14c sample
sample is a regular file
shreyash@shreyash-hp:~/Hands_on_1$ ./14c folder1/
folder1/ is a directory
==================================================
*/


