/*
============================================================================
Name : 7.c
Author : Shreyash Kumar Gupta
Description : Write a program to copy file1 into file2 ($cp file1 file2).
Date: 25th Aug, 2024.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main(int argv,char *argc[]){
	int fd1=open("7_file1.txt",O_RDONLY);
	if(fd1==-1){
		printf("Error while opening source file");
		close(fd1);
	}
	int fd2=open("7_file2.txt",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	if(fd2==-1){
		printf("Error while opening or creating destination file");
		close(fd2);
	}
	char content;

	while(read(fd1,&content,1))     //read one char at a time
	{
		write(fd2,&content,1);
	}
	printf("File copied\n");
	close(fd1);
	close(fd2);
	return 0;
}



