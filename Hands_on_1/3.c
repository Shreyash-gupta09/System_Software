/*
============================================================================
Name : 3.c
Author : Shreyash Kumar Gupta
Description :Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 24th Aug, 2024.
============================================================================
*/


#include<stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int c= creat("Program_3_file",0700);
	printf("\nNew file created");
	printf("\nFile Descriptor value is : %d\n",c);
	return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ gcc 3.c -o 3c
shreyash@shreyash-hp:~/Hands_on_1$ ./3c

New file created
File Descriptor value is : 3

============================================================================
*/
