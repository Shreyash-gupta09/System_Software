/*
============================================================================
Name : 8.c
Author : Shreyash Kumar Gupta
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read
              Close the file when end of file is reached.

Date: 25th Aug, 2024.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    char ch;


    fd = open(argv[1], O_RDONLY);


    while (read(fd, &ch, 1))  {                            // this loop will not terminate when line changed because \n is treated as a character in file
                 					 // "\n" will be read and written on terminal hence line change seen loop only terminates when eof is found and read
                                                         //system call returns 0
        write(1, &ch, 1);
    }

    close(fd);

    return 0;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./8c 8_file.txt
Hello THIS CONTENT IS BEING READ AND DISPLAYED ON THE TERMINAL....
program contains  a simple while loop
to read all the characters from this file and display on the terminal..
============================================================================
*/
