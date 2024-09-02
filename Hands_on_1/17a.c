/*
============================================================================
Name : 17a.c
Author : Shreyash Kumar Gupta
Description : Write a program to simulate online ticket reservation. Implement write
              Write a program to open a file, store a ticket number and exit. Write a separate program, to
              open the file, implement write lock, read the ticket number, increment the number and print
              the new ticket number then close the file.
Date: 27th Aug, 2024.
============================================================================
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
	int fd;
	struct {
		int ticket_no;
	       } db;
	db.ticket_no = 10;
	fd = open("17_ticket", O_CREAT|O_RDWR, 0744);
	write(fd, &db, sizeof(db));
	close(fd);
	fd = open("17_ticket", O_RDONLY);
	read(fd, &db, sizeof(db));
	printf("Ticket no: %d\n", db.ticket_no);
	close(fd);
}

/* OUTPUT
=====================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./17ac
Ticket no: 10
=====================================================
*/
