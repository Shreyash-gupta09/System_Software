/*
============================================================================
Name : 1c.c
Author : Shreyash Kumar Gupta
Description : Create FIFO files using(mkfifo Library Function or mknod system call)
Date: 24th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/stat.h>
int main(int argc,char *argv[]){

	int f=mkfifo(argv[1],0777);    // here we can also directly give name of the fifo instead of argv[1]
	if(f==0){
		printf("\nFIFO special file is created\n");
	}
	else
		perror("\nFIFO not created");

	return 0;
}



/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./1c Fifofile

FIFO special file is created

============================================================================
*/
