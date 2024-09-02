/*
============================================================================
Name : 4.c
Author : Shreyash Kumar Gupta
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also
Date: 24th Aug, 2024.
============================================================================
*/


#include<stdio.h>
#include <fcntl.h>

int main(int argv,char *argc[])
{
        int o=open("openme.txt",O_RDWR);
        if(o>=0)
		printf("\nFile opened with descriptor value = %d \n",o);
	else
		perror("\nFile cannot be opened");

	int x=open("Program_file_4",O_RDWR | O_CREAT | O_EXCL,0700);         //this file will only be opened if it does not exist previously
        if(x>=0)
                printf("\nFile created and opened with O_EXCL flag with descriptor value = %d \n",o);
        else
                perror("\nFile cannot be opened");
}




/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./4c

File opened with descriptor value = 3

File cannot be opened: File exists

============================================================================
*/
