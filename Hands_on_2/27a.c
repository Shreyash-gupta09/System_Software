/*
============================================================================
Name :27a.c
Author :Shreyash Kumar Gupta
Description :Write a program to receive messages from the message queue.
		a. with 0 as a flag
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

    // Receive message with blocking flag
    if (msgrcv(msgid, &message, sizeof(message.text), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Received (Blocking): %s\n", message.text);
    return 0;
}
/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./27ac
Received (Blocking): Hello, Message Queue!
============================================================================
*/
