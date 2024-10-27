/*
============================================================================
Name :25.c
Author :Shreyash Kumar Gupta
Description :Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 17th September,2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds msg_info;

    key = ftok("msg_queue_file_25", 'B');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if (msgctl(msgid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    printf("Access Permissions: %o\n", msg_info.msg_perm.mode);
    printf("Owner UID: %d\n", msg_info.msg_perm.uid);
    printf("Owner GID: %d\n", msg_info.msg_perm.gid);
    printf("Last Message Sent Time: %s", ctime(&msg_info.msg_stime));
    printf("Last Message Received Time: %s", ctime(&msg_info.msg_rtime));
    printf("Last Change Time: %s", ctime(&msg_info.msg_ctime));
    printf("Size of the Queue: %lu bytes\n", msg_info.__msg_cbytes);
    printf("Number of Messages in the Queue: %lu\n", msg_info.msg_qnum);
    printf("Maximum Number of Bytes Allowed: %lu\n", msg_info.msg_qbytes);
    printf("PID of Last Msgsnd: %d\n", msg_info.msg_perm.__key);
    printf("PID of Last Msgrcv: %d\n", msg_info.msg_perm.__key);


    return 0;
}


/* OUTPUT
============================================================================
Access Permissions: 666
Owner UID: 1000
Owner GID: 1000
Last Message Sent Time: Thu Jan  1 05:30:00 1970
Last Message Received Time: Thu Jan  1 05:30:00 1970
Last Change Time: Sat Sep 21 16:46:15 2024
Size of the Queue: 0 bytes
Number of Messages in the Queue: 0
Maximum Number of Bytes Allowed: 16384
PID of Last Msgsnd: 1107567811
PID of Last Msgrcv: 1107567811
============================================================================
*/
