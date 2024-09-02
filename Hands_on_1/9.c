/*
============================================================================
Name : 9.c
Author : Shreyash Kumar Gupta
Description : Write a program to print the following information about a given file.
                        a. inode
                        b. number of hard links
                        c. uid
                        d. gid
                        e. size
                        f. block size
                        g. number of blocks
                        h. time of last access
                        i. time of last modification
                        j. time of last change
Date: 25th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
int main(int argc, char *argv[]) {
    struct stat s;  // Using 's' as the structure name

    // Check if file name is provided
    if (argc != 2) {
        printf("File name not provided\n");
        return 1;
    }

    // Get file statistics
    if (stat(argv[1], &s) < 0) {
        perror("stat");
        return 1;
    }

    // Print file information

    printf("File: %s\n", argv[1]);
    printf("Inode: %ld\n", s.st_ino);
    printf("Number of hard links: %ld\n", s.st_nlink);
    printf("UID: %d\n", s.st_uid);
    printf("GID: %d\n", s.st_gid);
    printf("Size: %ld bytes\n", s.st_size);
    printf("Block size: %ld bytes\n", s.st_blksize);
    printf("Number of blocks: %ld\n", s.st_blocks);
    printf("Time of last access: %s", ctime(&s.st_atime));
    printf("Time of last modification: %s", ctime(&s.st_mtime));
    printf("Time of last change: %s", ctime(&s.st_ctime));

    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./9c 9_file_info
File: 9_file_info
Inode: 3939197
Number of hard links: 1
UID: 1000
GID: 1000
Size: 188 bytes
Block size: 4096 bytes
Number of blocks: 8
Time of last access: Wed Aug 28 01:22:51 2024
Time of last modification: Thu Aug 22 00:54:07 2024
Time of last change: Thu Aug 22 00:54:07 2024

============================================================================
*/
