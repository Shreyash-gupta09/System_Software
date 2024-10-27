/*
============================================================================
Name :27b.c
Author :Shreyash Kumar Gupta
Description :Write a program to receive messages from the message queue.
		b. with IPC_NOWAIT as a flag
Date: 19th September,2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_TEXT 100

struct msg_buffer {
    long msg_type;
    char text[MAX_TEXT];
};

int main() {
    key_t key = ftok("msg_queue_file_26", 'B');
    int msgid = msgget(key, 0666);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct msg_buffer message;

    // Receive message with IPC_NOWAIT flag
    if (msgrcv(msgid, &message, sizeof(message.text), 1, IPC_NOWAIT) == -1) {
        perror("msgrcv (IPC_NOWAIT)");
        exit(EXIT_FAILURE);
    }

    printf("Received (Non-blocking): %s\n", message.text);
    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./27bc
Received (Non-blocking): Hello, Message Queue!
============================================================================
*/
