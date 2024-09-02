/*
============================================================================
Name : 27a.c
Author : Shreyash Kumar Gupta
Description : Write a program to execute ls -Rl by the following system calls
	      a. execl
Date: 29th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    execl("/bin/ls", "ls", "-Rl", NULL);
    perror("execl failed");
    return 1;
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./27ac
.:
total 1128
-rw-rw-r-- 1 shreyash shreyash   1289 Aug 23 00:33  10.c
-rwxrwxr-x 1 shreyash shreyash  16216 Aug 23 00:32  10c
-rwx------ 1 shreyash shreyash     30 Aug 23 00:32  10_file
-rw-rw-r-- 1 shreyash shreyash   1274 Aug 23 00:15  11.c
-rwxrwxr-x 1 shreyash shreyash  16160 Aug 23 00:15  11c
-rw------- 1 shreyash shreyash    116 Aug 23 00:15  11_file
-rw-rw-r-- 1 shreyash shreyash    903 Aug 23 01:17  12.c
-rwxrwxr-x 1 shreyash shreyash  16072 Aug 23 01:15  12c
-rw-rw-r-- 1 shreyash shreyash      0 Aug 23 01:15  12_file
-rw-rw-r-- 1 shreyash shreyash   1391 Aug 24 01:07  13.c
-rwxrwxr-x 1 shreyash shreyash  16128 Aug 24 01:06  13c
-rw-rw-r-- 1 shreyash shreyash   1451 Aug 23 22:48  14.c
-rwxrwxr-x 1 shreyash shreyash  16088 Aug 23 22:42  14c
-rw-rw-r-- 1 shreyash shreyash   1123 Aug 23 14:46  15.c
-rwxrwxr-x 1 shreyash shreyash  16016 Aug 23 22:36  15c
-rw-rw-r-- 1 shreyash shreyash   1323 Aug 29 00:39  16.c
-rwxrwxr-x 1 shreyash shreyash  16288 Aug 24 13:43  16c
-rw-rwSr-- 1 shreyash shreyash      0 Aug 24 13:42  16_lock
-rw-rw-r-- 1 shreyash shreyash   1473 Aug 26 23:22  17a.c
-rwxrwxr-x 1 shreyash shreyash  16168 Aug 26 20:07  17ac
-rw-rw-r-- 1 shreyash shreyash   1436 Aug 26 20:16  17b.c
-rwxrwxr-x 1 shreyash shreyash  16296 Aug 26 20:10  17bc
-rwxr--r-- 1 shreyash shreyash      4 Aug 26 20:11  17_ticket
-rw-rw-r-- 1 shreyash shreyash   1055 Aug 26 23:55  18a.c
-rwxrwxr-x 1 shreyash shreyash  16168 Aug 27 00:28  18ac
-rw-rw-r-- 1 shreyash shreyash   2147 Aug 27 00:34  18b.c
-rwxrwxr-x 1 shreyash shreyash  16416 Aug 27 00:34  18bc
-rwxrwxr-x 1 shreyash shreyash  16088 Aug 26 23:44  18c
-rw------- 1 shreyash shreyash     24 Aug 27 00:39  18_file
-rw-rw-r-- 1 shreyash shreyash    666 Aug 28 00:38  19.c
-rwxrwxr-x 1 shreyash shreyash  16024 Aug 28 00:37  19c
-rwxrwxr-x 1 shreyash shreyash  16040 Aug 13 19:52  1a
-rw-rw-r-- 1 shreyash shreyash    460 Aug 13 19:51  1a.c
-rwxrwxr-x 1 shreyash shreyash  16032 Aug 13 20:01  1b
-rw-rw-r-- 1 shreyash shreyash    505 Aug 13 20:00  1b.c
-rwxrwxr-x 1 shreyash shreyash  16032 Aug 13 20:41  1c
-rw-rw-r-- 1 shreyash shreyash    438 Aug 13 20:41  1c.c
-rw-rw-r-- 1 shreyash shreyash    664 Aug 28 01:09  20.c
-rwxrwxr-x 1 shreyash shreyash  15992 Aug 28 01:17  20c
-rw-rw-r-- 1 shreyash shreyash   1095 Aug 28 01:22  21.c
-rwxrwxr-x 1 shreyash shreyash  16160 Aug 28 01:17  21c
-rw-rw-r-- 1 shreyash shreyash   1283 Aug 28 21:38  22.c
-rwxrwxr-x 1 shreyash shreyash  16160 Aug 28 21:36  22c
-rw-r--r-- 1 shreyash shreyash     45 Aug 28 21:36  22_file.txt
-rw-rw-r-- 1 shreyash shreyash   1457 Aug 29 01:21  23.c
-rwxrwxr-x 1 shreyash shreyash  16160 Aug 28 23:57  23c
-rw-rw-r-- 1 shreyash shreyash   1023 Aug 29 16:59  24.c
-rwxrwxr-x 1 shreyash shreyash  16208 Aug 29 16:59  24c
-rw-rw-r-- 1 shreyash shreyash   1671 Aug 29 17:24  25.c
-rwxrwxr-x 1 shreyash shreyash  16256 Aug 29 17:23  25c
-rw-rw-r-- 1 shreyash shreyash    906 Aug 29 18:35  26a.c
-rwxrwxr-x 1 shreyash shreyash  15952 Aug 29 18:08  26ac
-rw-rw-r-- 1 shreyash shreyash    989 Aug 29 18:35  26b.c
-rwxrwxr-x 1 shreyash shreyash  16088 Aug 29 18:12  26bc
-rw-rw-r-- 1 shreyash shreyash    627 Aug 29 19:04  27a.c
-rwxrwxr-x 1 shreyash shreyash  15992 Aug 29 19:04  27ac
-rw-rw-r-- 1 shreyash shreyash    329 Aug 14 20:58  2.c
-rwxrwxr-x 1 shreyash shreyash  15768 Aug 14 21:03  2c
-rw-rw-r-- 1 shreyash shreyash    378 Aug 19 23:05  3.c
-rwxrwxr-x 1 shreyash shreyash  15992 Aug 19 23:06  3c
-rw-rw-r-- 1 shreyash shreyash    648 Aug 19 23:06  4.c
-rwxrwxr-x 1 shreyash shreyash  16032 Aug 19 23:06  4c
-rwx------ 1 shreyash shreyash      0 Aug 19 23:21  5_1.txt
-rwx------ 1 shreyash shreyash      0 Aug 19 23:21  5_2.txt
-rwx------ 1 shreyash shreyash      0 Aug 19 23:21  5_3.txt
-rwx------ 1 shreyash shreyash      0 Aug 19 23:21  5_4.txt
-rwx------ 1 shreyash shreyash      0 Aug 19 23:21  5_5.txt
-rw-rw-r-- 1 shreyash shreyash    608 Aug 19 23:16  5.c
-rwxrwxr-x 1 shreyash shreyash  15992 Aug 19 23:20  5c
-rw-rw-r-- 1 shreyash shreyash 164768 Aug 19 23:32  5_output.png
-rw-rw-r-- 1 shreyash shreyash    400 Aug 29 18:48  6.c
-rwxrwxr-x 1 shreyash shreyash  16088 Aug 22 08:34  6c
-rw-rw-r-- 1 shreyash shreyash    670 Aug 22 08:52  7.c
-rwxrwxr-x 1 shreyash shreyash  16208 Aug 22 00:15  7c
-rw-rw-r-- 1 shreyash shreyash     61 Aug 21 23:59  7_file1.txt
-rw------- 1 shreyash shreyash     61 Aug 22 00:15  7_file2.txt
-rw-rw-r-- 1 shreyash shreyash    843 Aug 22 08:52  8.c
-rwxrwxr-x 1 shreyash shreyash  16128 Aug 22 00:24  8c
-rw-rw-r-- 1 shreyash shreyash    177 Aug 22 00:33  8_file.txt
-rw-rw-r-- 1 shreyash shreyash   1325 Aug 23 22:16  9.c
-rwxrwxr-x 1 shreyash shreyash  16168 Aug 22 09:18  9c
-rw-rw-r-- 1 shreyash shreyash    188 Aug 22 00:54  9_file_info
-rw-rw-r-- 1 shreyash shreyash  42408 Aug 22 00:54  9_output.png
prwxrwxr-x 1 shreyash shreyash      0 Aug 13 20:41  Fifofile
drwxrwxr-x 3 shreyash shreyash   4096 Aug 13 19:13  folder1
-rw-rw-r-- 2 shreyash shreyash     45 Aug 13 20:03  hardlink
-rw-rw-r-- 2 shreyash shreyash     57 Aug 13 20:02  hardlink1
-rw-rw-r-- 1 shreyash shreyash     50 Aug 14 22:33  openme.txt
-rw-rw-r-- 1 shreyash shreyash 212278 Aug 14 21:07 'output 2c.png'
-rwx------ 1 shreyash shreyash      0 Aug 19 23:06  Program_3_file
-rwx------ 1 shreyash shreyash      0 Aug 19 23:06  Program_file_4
-rw-rw-r-- 1 shreyash shreyash      0 Aug 23 22:43  sample
lrwxrwxrwx 1 shreyash shreyash     46 Aug 13 19:17  softlink -> /home/shreyash/Hands_on_1/folder1/folder2/file
lrwxrwxrwx 1 shreyash shreyash     47 Aug 13 19:57  softlink1 -> /home/shreyash/Hands_on_1/folder1/folder2/file2

./folder1:
total 4
drwxrwxr-x 2 shreyash shreyash 4096 Aug 13 20:02 folder2

./folder1/folder2:
total 16
-rw-rw-r-- 1 shreyash shreyash 64 Aug 13 20:02 file
-rw-rw-r-- 2 shreyash shreyash 45 Aug 13 20:03 file1
-rw-rw-r-- 1 shreyash shreyash 35 Aug 13 19:55 file2
-rw-rw-r-- 2 shreyash shreyash 57 Aug 13 20:02 file3

============================================================================
*/
