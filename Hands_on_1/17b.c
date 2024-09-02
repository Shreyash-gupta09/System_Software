/*
============================================================================
Name : 17b.c
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

	struct {
		int ticket_no;
	} db;
	struct flock lock = {F_WRLCK,0,0,0,0};   // set write_lock type to flock instance lock.
	int fd;
	fd = open("17_ticket", O_RDWR);


	printf("Before entering into critical section\n applying write lock...");
	fcntl(fd, F_SETLKW, &lock);
	printf("Inside the critical section\n");

	// Read after acquiring lock, so that no inconsistencies happen
	read(fd, &db, sizeof(db));
	printf("Current ticket number: %d\n", db.ticket_no);
	db.ticket_no++; // Actually incrementing the ticket number

	// Because of initial read, fd is now pointing to the end of thefile, so we have to reposition to the beginning of the file
	lseek(fd, 0, SEEK_SET);
	write(fd, &db, sizeof(db));

	printf("Press enter to unlock\n");
	getchar();

	// Unlock the file
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("Exited critical section\n");
}

/*
==============================================================
OUTPUT
shreyash@shreyash-hp:~/Hands_on_1$ ./17bc
Before entering into critical section
 applying write lock...Inside the critical section
Current ticket number: 10
Press enter to unlock

Exited critical section

shreyash@shreyash-hp:~/Hands_on_1$ ./17bc
Before entering into critical section
 applying write lock...Inside the critical section
Current ticket number: 11
Press enter to unlock

Exited critical section

shreyash@shreyash-hp:~/Hands_on_1$ ./17bc
Before entering into critical section
 applying write lock...Inside the critical section
Current ticket number: 12
Press enter to unlock

Exited critical section
================================================================
