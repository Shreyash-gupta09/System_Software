/*
============================================================================
Name : 13.c
Author : Shreyash Kumar Gupta
Description : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
              verify whether the data is available within 10 seconds or not (check in $man 2 select).
Date: 26th Aug, 2024.
============================================================================
*/


#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    struct timeval timeout;

    // Initialize the set of file descriptors and the timeout
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Wait for input on STDIN for up to 10 seconds
    int result = select(1, &readfds, NULL, NULL, &timeout);

    if (result > 0) {
        printf("Data is available now.\n");
        char buffer[1024];
        int bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        if (bytesRead >= 0) {
            buffer[bytesRead] = '\0';
            printf("Input received: %s", buffer);

	}
    }
	else if (result == 0) {
        printf("No data within 10 seconds.\n");
    }
	else {
        printf("error occured");
    }

    return 0;
}

/*	OUTPUT :-
===================================================
WHEN NO DATA IS GIVEN IN STDIN WITHIN 10 SECONDS

shreyash@shreyash-hp:~/Hands_on_1$ ./13c
No data within 10 seconds.


WHEN DATA IS GIVEN WITHIN 10 SECONDS

shreyash@shreyash-hp:~/Hands_on_1$ ./13c
hello
Data is available now.
Input received: hello
===================================================
*/
