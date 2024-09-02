/*
============================================================================
Name : 16.c
Author : Shreyash Kumar Gupta
Description : Write a program to perform mandatory locking.
                        a. Implement write lock
                        b. Implement read lock
Date: 26th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void lock_file(int fd, short lock_type) {
    struct flock lock;
    lock.l_type = lock_type;  // F_RDLCK for read lock, F_WRLCK for write lock
    lock.l_whence = SEEK_SET; // Start of the file
    lock.l_start = 0;         // Offset from l_whence
    lock.l_len = 0;           // Length of the lock (0 means until EOF)

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl");
        exit(1);
    }
}

int main() {
    int fd = open("16_lock", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("Applying write lock...\n");
    lock_file(fd, F_WRLCK);   // Apply write lock
    printf("Write lock applied. Press Enter to unlock the file...\n");
    getchar();

    printf("Releasing write lock and applying read lock...\n");
    lock_file(fd, F_UNLCK);

    lock_file(fd, F_RDLCK);   // Apply read lock
    printf("Read lock applied. Press enter to unlock the file...\n");
    getchar();

    printf("Releasing read lock...\n");
    lock_file(fd, F_UNLCK);

    printf("END...\n");
    close(fd);
    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./16c
Applying write lock...
Write lock applied. Press Enter to unlock the file...

Releasing write lock and applying read lock...
Read lock applied. Press enter to unlock the file...

Releasing read lock...
END...
shreyash@shreyash-hp:~/Hands_on_1$ 

============================================================================
*/
