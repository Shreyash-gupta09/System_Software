/*
============================================================================
Name : 1b.c
Author : Shreyash Kumar Gupta
Description : Create hard link files using (i) shell command (ii) system call
Date: 24th Aug, 2024.
============================================================================
*/

//(i) You can create hardlink through  ln command.



//(ii) Using System call (link)

#include<stdio.h>
#include<unistd.h>
int main(int argc, char *argv[]){

        int l= link(argv[1],argv[2]);
        if(l==0){
                printf("\nHardLink is created succsesfully");
        }
        else
                perror("\nCan't link the files");
return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./1b ./folder1/folder2/file3 hardlink1

HardLink is created succsesfully
============================================================================
*/


