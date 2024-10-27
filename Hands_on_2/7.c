/*
============================================================================
Name :7.c
Author :Shreyash Kumar Gupta
Description : Write a simple program to print the created thread ids.
Date: 11th September,2024.
============================================================================
*/

#include <pthread.h>
#include <stdio.h>

void* thread_function(void* arg) {
    pthread_t thread_id = pthread_self();
    printf("Thread ID: %lu\n", (unsigned long)thread_id);
    return NULL;
}

int main() {
    pthread_t threads[3];

    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
/* OUTPUT
============================================================================
Thread ID: 123561024947904
Thread ID: 123561003976384
Thread ID: 123561014462144
============================================================================
*/
