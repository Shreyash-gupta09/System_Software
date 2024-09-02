/*
============================================================================
Name : 5.c
Author : Shreyash Kumar Gupta
Description :Write a program to create five new files with infinite loop. Execute the program in the background
             and check the file descriptor table at /proc/pid/fd.
Date: 24th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>

void main(int argv,char *argc[]){

        int f1 =creat(argc[1],0700);
        int f2 =creat(argc[2],0700);
        int f3 =creat(argc[3],0700);
        int f4 =creat(argc[4],0700);
        int f5 =creat(argc[5],0700);

        printf("\nFile descriptors are f1=%d\tf2=%d\tf3=%d\tf4=%d\tf5=%d\t\n",f1,f2,f3,f4,f5);

        while(1);
}

