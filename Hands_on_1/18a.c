/*
============================================================================
Name : 18a.c
Author : Shreyash Kumar Gupta
Description : Write a program to perform Record locking.
              a. Implement write
              b. Implement read lock
              Create three records in a file. Whenever you access a particular record, first lock it then modify/access
              to avoid race condition.
Date: 27th Aug, 2024.
============================================================================
*/


#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main() {
	int i, fd;
	struct {
		int train_num;
		int ticket_count;
		} db[3];
	for (i=0; i<3; i++) {
	db[i].train_num = i+1;
	db[i].ticket_count = 0;
	}

	// Writing all 3 records to record.txt file

	fd = open("18_file", O_RDWR | O_CREAT,0600);
	write(fd, db, sizeof(db));
	close(fd);

	fd=open("18_file",O_RDWR);
	read(fd, db, sizeof(db));
        printf("Train no: %d\n", db[0].train_num);
	printf("1st Train ticket count : %d\n", db[0].ticket_count);
	printf("Train no: %d\n", db[1].train_num);
	printf("2nd Train ticket count : %d\n", db[1].ticket_count);
	printf("Train no: %d\n", db[2].train_num);
	printf("3rd Train ticket count : %d\n", db[2].ticket_count);

	close(fd);
}
/*
OUTPUT
=======================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./18ac
Train no: 1
1st Train ticket count : 0
Train no: 2
2nd Train ticket count : 0
Train no: 3
3rd Train ticket count : 0
========================================================
*/
