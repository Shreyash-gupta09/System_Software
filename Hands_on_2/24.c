/*
============================================================================
Name :24.c
Author :Shreyash Kumar Gupta
Description :Write a program to create a message queue and print the key and message queue id.
Date: 17th September,2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main() {
    key_t key;
    int msgid;

    // Generate a unique key for the message queue
    key = ftok("msg_queue_file", 'B'); // 'B' can be any character
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);


    return 0;
}

/* OUTPUT
============================================================================
Key: 1107567523
Message Queue ID: 0
============================================================================
*/
