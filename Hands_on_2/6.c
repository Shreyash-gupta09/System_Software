/*
============================================================================
Name :6.c
Author :Shreyash Kumar Gupta
Description : Write a simple program to create three threads.
Date: 11th September,2024.
============================================================================
*/

#include <pthread.h>
#include <stdio.h>

void* thread_function(void* arg) {
    printf("Thread is running\n");
    return NULL;
}

int main() {
    pthread_t threads[3];

    for (int i = 0; i < 3; i++) {
	if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread");
    	}
    }

    for (int i = 0; i < 3; i++) {
      pthread_join(threads[i], NULL);
    }

    return 0;
}

/* OUTPUT
============================================================================
Thread is running
Thread is running
Thread is running
============================================================================
*/
