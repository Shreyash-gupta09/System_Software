/*
============================================================================
Name : 1a.c
Author : Shreyash Kumar Gupta
Description : Create soft link files using (i) shell command (ii) system call
Date: 24th Aug, 2024.
============================================================================
*/

//(i) You can create softlink through  ln -s command.



//(ii) Using System call (symlink)

#include<stdio.h>
#include<unistd.h>
int main(int argc, char *argv[]){

	int l= symlink(argv[1],argv[2]);
	if(l==0){
		printf("\nSoftLink is created succsesfully");
	}
	else
		perror("\nCan't link the files");
return 0;
}

/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./1a ./folder1/folder2/file2 softlink1

SoftLink is created succsesfully

============================================================================
*/
