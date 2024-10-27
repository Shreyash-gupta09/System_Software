/*
============================================================================
Name : 2.c
Author : Shreyash Kumar Gupta
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 3rd September,2024.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>

void print_limit(int resource, const char *name) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == 0) {
        printf("%s: soft limit = %ld, hard limit = %ld\n", name, (long)limit.rlim_cur, (long)limit.rlim_max);
    } else {
        perror("getrlimit");
    }
}

int main() {
    print_limit(RLIMIT_CPU, "CPU time");
    print_limit(RLIMIT_FSIZE, "File size");
    print_limit(RLIMIT_DATA, "Data segment size");
    print_limit(RLIMIT_STACK, "Stack size");
    print_limit(RLIMIT_CORE, "Core file size");
    print_limit(RLIMIT_RSS, "Resident set size");
    print_limit(RLIMIT_NOFILE, "Number of open files");
    print_limit(RLIMIT_AS, "Address space size");
    print_limit(RLIMIT_NPROC, "Number of processes");
    print_limit(RLIMIT_MEMLOCK, "Locked memory size");
    print_limit(RLIMIT_LOCKS, "Number of file locks");
    print_limit(RLIMIT_SIGPENDING, "Queued signals");
    print_limit(RLIMIT_MSGQUEUE, "POSIX message queues");
    print_limit(RLIMIT_NICE, "Nice value");
    print_limit(RLIMIT_RTPRIO, "Real-time priority");
    print_limit(RLIMIT_RTTIME, "Real-time CPU time");

    return 0;
}


/* OUTPUT
============================================================================
CPU time: soft limit = -1, hard limit = -1
File size: soft limit = -1, hard limit = -1
Data segment size: soft limit = -1, hard limit = -1
Stack size: soft limit = 8388608, hard limit = -1
Core file size: soft limit = 0, hard limit = -1
Resident set size: soft limit = -1, hard limit = -1
Number of open files: soft limit = 1024, hard limit = 1048576
Address space size: soft limit = -1, hard limit = -1
Number of processes: soft limit = 28822, hard limit = 28822
Locked memory size: soft limit = 953581568, hard limit = 953581568
Number of file locks: soft limit = -1, hard limit = -1
Queued signals: soft limit = 28822, hard limit = 28822
POSIX message queues: soft limit = 819200, hard limit = 819200
Nice value: soft limit = 0, hard limit = 0
Real-time priority: soft limit = 0, hard limit = 0
Real-time CPU time: soft limit = -1, hard limit = -1

============================================================================
*/
