/*
============================================================================
Name :26.c
Author :Shreyash Kumar Gupta
Description :Write a program to send messages to the message queue. Check $ipcs -q
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
    long msg_type;        // Message type
    char text[MAX_TEXT];  // Message text
};

int main() {
    key_t key = ftok("msg_queue_file_26", 'B'); // Generate a unique key
    int msgid = msgget(key, 0666 | IPC_CREAT); // Create message queue

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct msg_buffer message;
    message.msg_type = 1; // Set message type

    // Prepare and send a message
    snprintf(message.text, sizeof(message.text), "Hello, Message Queue!");

    if (msgsnd(msgid, &message, sizeof(message.text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Sent: %s\n", message.text);
    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./26c
Sent: Hello, Message Queue!

shreyash@shreyash-hp:~/Hands_on_2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages

0xffffffff 3          shreyash   666        100          1
============================================================================
*/
