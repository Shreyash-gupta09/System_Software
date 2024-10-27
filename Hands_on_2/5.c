/*
============================================================================
Name : 5.c
Author : Shreyash Kumar Gupta
Description : Write a program to print the system limitation of
		a. maximum length of the arguments to the exec family of functions.
		b. maximum number of simultaneous process per user id.
		c. number of clock ticks (jiffy) per second.
		d. maximum number of open files
		e. size of a page
		f. total number of pages in the physical memory
		g. number of currently available pages in the physical memory.
Date: 9th September,2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    long arg_max = sysconf(_SC_ARG_MAX);
    if (arg_max == -1) {
        perror("sysconf for ARG_MAX failed");
    } else {
        printf("Maximum length of arguments to the exec family of functions: %ld\n", arg_max);
    }

    long child_max = sysconf(_SC_CHILD_MAX);
    if (child_max == -1) {
        perror("sysconf for CHILD_MAX failed");
    } else {
        printf("Maximum number of simultaneous processes per user ID: %ld\n", child_max);
    }

    long clock_ticks = sysconf(_SC_CLK_TCK);
    if (clock_ticks == -1) {
        perror("sysconf for CLK_TCK failed");
    } else {
        printf("Number of clock ticks (jiffy) per second: %ld\n", clock_ticks);
    }

    long open_max = sysconf(_SC_OPEN_MAX);
    if (open_max == -1) {
        perror("sysconf for OPEN_MAX failed");
    } else {
        printf("Maximum number of open files: %ld\n", open_max);
    }

    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        perror("sysconf for PAGESIZE failed");
    } else {
        printf("Size of a memory page: %ld bytes\n", page_size);
    }

    long total_pages = sysconf(_SC_PHYS_PAGES);
    if (total_pages == -1) {
        perror("sysconf for PHYS_PAGES failed");
    } else {
        printf("Total number of pages in physical memory: %ld\n", total_pages);
    }

    long avail_pages = sysconf(_SC_AVPHYS_PAGES);
    if (avail_pages == -1) {
        perror("sysconf for AVPHYS_PAGES failed");
    } else {
        printf("Number of currently available pages in physical memory: %ld\n", avail_pages);
    }

    return 0;
}
/* OUTPUT
============================================================================
Maximum length of arguments to the exec family of functions: 2097152
Maximum number of simultaneous processes per user ID: 28823
Number of clock ticks (jiffy) per second: 100
Maximum number of open files: 1024
Size of a memory page: 4096 bytes
Total number of pages in physical memory: 1862472
Number of currently available pages in physical memory: 265377
============================================================================
*/
