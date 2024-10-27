/*
============================================================================
Name :31.c
Author :Shreyash Kumar Gupta
Description :Write a program to create a semaphore and initialize value to the semaphore.
		a. create a binary semaphore
		b. create a counting semaphore
Date: 20th September,2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BINARY_SEM_NAME "/binary_sem"
#define COUNTING_SEM_NAME "/counting_sem"

int main() {
    sem_t *binary_sem;
    sem_t *counting_sem;

    // Create and initialize a binary semaphore
    binary_sem = sem_open(BINARY_SEM_NAME, O_CREAT | O_EXCL, 0644, 1); // Initial value 1 (unlocked)
    if (binary_sem == SEM_FAILED) {
        perror("Failed to create binary semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Binary semaphore created and initialized.\n");

    // Create and initialize a counting semaphore
    counting_sem = sem_open(COUNTING_SEM_NAME, O_CREAT | O_EXCL, 0644, 5); // Initial value 5
    if (counting_sem == SEM_FAILED) {
        perror("Failed to create counting semaphore");
        sem_close(binary_sem);
        sem_unlink(BINARY_SEM_NAME);
        exit(EXIT_FAILURE);
    }
    printf("Counting semaphore created and initialized with value 5.\n");

    // Clean up
    sem_close(binary_sem);
    sem_close(counting_sem);
    sem_unlink(BINARY_SEM_NAME);
    sem_unlink(COUNTING_SEM_NAME);

    return 0;
}


/* OUTPUT
============================================================================
Binary semaphore created and initialized.
Counting semaphore created and initialized with value 5.
============================================================================
*/
