/*
============================================================================
Name : 10.c
Author : Shreyash Kumar Gupta
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
              bytes (use lseek) and write again 10 bytes.
               a. check the return value of lseek
               b. open the file with od and check the empty spaces in between the data.
Date: 25th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argv, char *argc[])
{
	int fd = open("10_file", O_RDWR | O_CREAT, S_IRWXU);
	if (fd == -1)
	{
		perror("Error while opening file");
		close(fd);
		return 0;
	}

	char s[10] = "ABCDEFGHIJ";
	write(fd, s, 10);
	int o = lseek(fd, 10, SEEK_CUR);
	printf("Value returned by lseek() after writing 10 bytes and moving pointer by 10 bytes = %d\n", o);
	write(fd, s, 10);
	o = lseek(fd, 0, SEEK_CUR);
	printf("Current value of pointer after writing 10 more bytes = %d\n", o);
	return 0;
}

/* OUTPUT
===================================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./10c

Value returned by lseek() after writing 10 bytes and moving pointer by 10 bytes = 20
Current value of pointer after writing 10 more bytes = 30

shreyash@shreyash-hp:~/Hands_on_1$ od -c 10_file

0000000   A   B   C   D   E   F   G   H   I   J  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0   A   B   C   D   E   F   G   H   I   J
0000036
===================================================================================
*/
