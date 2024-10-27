/*
============================================================================
Name :30.c
Author :Shreyash Kumar Gupta
Description :Write a program to create a shared memory.
		a. write some data to the shared memory
		b. attach with O_RDONLY and check whether you are able to overwrite.
		c. detach the shared memory
		d. remove the shared memory
Date: 19th September,2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory

int main() {
    key_t key = ftok("shmfile", 65);  // Generate unique key
    int shm_id;

    // Step a: Create shared memory segment
    shm_id = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Step a: Attach to the shared memory and write data
    char *data = (char *)shmat(shm_id, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Writing data to shared memory...\n");
    strcpy(data, "Hello, this is shared memory!");

    // Display written data
    printf("Data in shared memory: %s\n", data);

    // Detach from shared memory after writing
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Step b: Attach with O_RDONLY and attempt to overwrite
    data = (char *)shmat(shm_id, NULL, SHM_RDONLY);
    if (data == (char *)-1) {
        perror("shmat (O_RDONLY)");
        exit(EXIT_FAILURE);
    }
    printf("\nAttempting to overwrite in read-only mode...\n");
    if (strcpy(data, "Overwrite attempt!") == NULL) {
        perror("strcpy");
    } else {
        printf("Overwrite successful (this shouldn't happen).\n");
    }
    // Display data to confirm no overwriting
    printf("Data in shared memory after attempt: %s\n", data);

    // Step c: Detach from shared memory
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Step d: Remove the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory removed successfully.\n");

    return 0;
}

/* OUTPUT
============================================================================
Writing data to shared memory...
Data in shared memory: Hello, this is shared memory!

Attempting to overwrite in read-only mode...
Segmentation fault (core dumped)
============================================================================
*/
