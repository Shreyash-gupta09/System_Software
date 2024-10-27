/*
============================================================================
Name :19a.c
Author :Shreyash Kumar Gupta
Description :Create a FIFO file by
		a. mknod command
		b. mkfifo command
		c. use strace command to find out, which command (mknod or mkfifo) is better.
		c. mknod system call
		d. mkfifo library function
Date: 17th September,2024.
============================================================================
*/

/*
(a).   Syntax = mknod fifo_file_name p
	Where fifo_file_name is the name of the FIFO file you want to create.
 	The p argument specifies that you are creating a FIFO (named pipe).

(b).   Syntax = mkfifo fifo_file_name

(c).   Syntax = strace -c mkfifo myfifo1

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 43.94    0.000156           8        18           mmap
 11.83    0.000042           7         6           openat
  8.73    0.000031          31         1           mknodat
  7.32    0.000026           3         8           close
  7.04    0.000025           5         5           read
  5.63    0.000020           3         6           fstat
  4.23    0.000015           3         5           mprotect
  3.94    0.000014           7         2         2 access
  2.54    0.000009           4         2           pread64
  1.13    0.000004           4         1           arch_prctl
  1.13    0.000004           4         1           rseq
  0.85    0.000003           1         3           brk
  0.85    0.000003           3         1           set_tid_address
  0.85    0.000003           3         1           set_robust_list
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         2         2 statfs
  0.00    0.000000           0         1           prlimit64
  0.00    0.000000           0         1           getrandom
------ ----------- ----------- --------- --------- ----------------
100.00    0.000355           5        66         4 total

		strace -c mknod myfifo p

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 19.75    0.000063          63         1           mknodat
 18.18    0.000058           3        18           mmap
 11.60    0.000037           4         8           close
 11.60    0.000037           7         5           mprotect
  8.15    0.000026           4         6           openat
  7.84    0.000025           5         5           read
  5.02    0.000016           8         2         2 statfs
  4.08    0.000013          13         1           munmap
  3.76    0.000012           2         6           fstat
  2.51    0.000008           2         3           brk
  1.57    0.000005           2         2         2 access
  1.25    0.000004           4         1           prlimit64
  0.94    0.000003           3         1           arch_prctl
  0.94    0.000003           3         1           set_tid_address
  0.94    0.000003           3         1           set_robust_list
  0.94    0.000003           3         1           getrandom
  0.94    0.000003           3         1           rseq
  0.00    0.000000           0         2           pread64
  0.00    0.000000           0         1           execve
------ ----------- ----------- --------- --------- ----------------
100.00    0.000319           4        66         4 total

Based on above two summary mknode is better than mkfifo as it takes less time

*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *fifo_name = "File1";

    // Create FIFO using mknod
    if (mknod(fifo_name, S_IFIFO | 0666, 0) == -1) {
        perror("mknod failed");
        return 1;
    }

    printf("FIFO %s created using mknod\n", fifo_name);

    const char *fifo_name1 = "File2";

    // Create FIFO using mkfifo
    if (mkfifo(fifo_name1, 0666) == -1) {
        perror("mkfifo failed");
        return 1;
    }

    printf("FIFO %s created using mkfifo\n", fifo_name1);
    return 0;
}



/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_2$ ./19c
FIFO File1 created using mknod
FIFO File2 created using mkfifo
============================================================================
*/
