/*
============================================================================
Name : 3.c
Author : Shreyash Kumar Gupta
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 3rd September,2024.
============================================================================
*/

#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

int main() {
    struct rlimit limit;

    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Previous soft limit of NOFILE: %ld\n", limit.rlim_cur);
        printf("Previous hard limit of NOFILE: %ld\n", limit.rlim_max);
    } else {
        perror("Failed to get limit");
        return 1;
    }

    limit.rlim_cur = 2048;
    limit.rlim_max = 4096;

    if (setrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("New limits set successfully!\n");
    } else {
        perror("Failed to set limit");
        return 1;
    }

    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Current soft limit of NOFILE: %ld\n", limit.rlim_cur);
        printf("Current hard limit of NOFILE: %ld\n", limit.rlim_max);
    } else {
        perror("Failed to get limit");
        return 1;
    }

    return 0;
}
/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./3c
Previous soft limit of NOFILE: 1024
Previous hard limit of NOFILE: 1048576
New limits set successfully!
Current soft limit of NOFILE: 2048
Current hard limit of NOFILE: 4096

============================================================================
*/
