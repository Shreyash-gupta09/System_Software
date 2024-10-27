/*
============================================================================
Name :28.c
Author :Shreyash Kumar Gupta
Description :Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 19th September,2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    key_t key = ftok("msg_queue_file", 'B');
    int msgid = msgget(key, 0666);

    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct msqid_ds buf;

    // Get the current message queue information
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl IPC_STAT");
        exit(EXIT_FAILURE);
    }

    printf("Current Permissions: %o\n", buf.msg_perm.mode & 0777);

    // Change the permission to 0600 (read/write for the owner)
    buf.msg_perm.mode = 0600;

    // Apply the changes to the message queue
    if (msgctl(msgid, IPC_SET, &buf) == -1) {
        perror("msgctl IPC_SET");
        exit(EXIT_FAILURE);
    }

    // Verify the change
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl IPC_STAT");
        exit(EXIT_FAILURE);
    }

    printf("Updated Permissions: %o\n", buf.msg_perm.mode & 0777);

    return 0;
}

/* OUTPUT
============================================================================
Current Permissions: 666
Updated Permissions: 600
============================================================================
*/
