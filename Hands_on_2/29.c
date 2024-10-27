/*
============================================================================
Name :29.c
Author :Shreyash Kumar Gupta
Description :Write a program to remove the message queue.
Date: 19th September,2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("msg_queue_file", 'B');
    int msgid = msgget(key, 0666);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Message queue with ID %d has been removed.\n", msgid);
    return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./29c
Message queue with ID 0 has been removed.
============================================================================
*/
