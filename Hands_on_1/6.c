/*
============================================================================
Name : 6.c
Author : Shreyash Kumar Gupta
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 25th Aug, 2024.
============================================================================
*/


#include<stdio.h>
#include<unistd.h>
int main(){
	char input_buffer[50];

	//0 is file descriptor for STDIN

	int n=read(0,input_buffer,50);
	//1 is file descriptor for STDOUT
	write(1,input_buffer,n);
	printf("Number of bytes read : %d\n",n);

}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ gcc 6.c -o 6c
shreyash@shreyash-hp:~/Hands_on_1$ ./6c
hello my name is shreyash
hello my name is shreyash
Number of bytes read : 26
shreyash@shreyash-hp:~/Hands_on_1$
============================================================================
*/

