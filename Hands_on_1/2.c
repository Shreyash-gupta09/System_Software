/*
============================================================================
Name : 2.c
Author : Shreyash Kumar Gupta
Description : Write a simple program to execute in an infinite loop at the background. Go to /proc directory and
              identify all the process related information in the corresponding proc directory.
Date: 24th Aug, 2024.
============================================================================
*/


#include <stdio.h>
void main(int argc,char *argv[])
{
	while(1);
}


/* OUTPUT
============================================================================
shreyash@shreyash-hp:~/Hands_on_1$ ./2c &
[1] 4429
shreyash@shreyash-hp:~/Hands_on_1$ cd /proc
shreyash@shreyash-hp:/proc$ cd 4429
shreyash@shreyash-hp:/proc/4429$ ls -lh
total 0
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 arch_status
dr-xr-xr-x  2 shreyash shreyash 0 Aug 30 18:34 attr
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 autogroup
-r--------  1 shreyash shreyash 0 Aug 30 18:34 auxv
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 cgroup
--w-------  1 shreyash shreyash 0 Aug 30 18:34 clear_refs
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 cmdline
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 comm
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 coredump_filter
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 cpu_resctrl_groups
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 cpuset
lrwxrwxrwx  1 shreyash shreyash 0 Aug 30 18:34 cwd -> /home/shreyash/Hands_on_1
-r--------  1 shreyash shreyash 0 Aug 30 18:34 environ
lrwxrwxrwx  1 shreyash shreyash 0 Aug 30 18:34 exe -> /home/shreyash/Hands_on_1/2c
dr-x------  2 shreyash shreyash 3 Aug 30 18:34 fd
dr-xr-xr-x  2 shreyash shreyash 0 Aug 30 18:34 fdinfo
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 gid_map
-r--------  1 shreyash shreyash 0 Aug 30 18:34 io
-r--------  1 shreyash shreyash 0 Aug 30 18:34 ksm_merging_pages
-r--------  1 shreyash shreyash 0 Aug 30 18:34 ksm_stat
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 latency
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 limits
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 loginuid
dr-x------  2 shreyash shreyash 0 Aug 30 18:34 map_files
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 maps
-rw-------  1 shreyash shreyash 0 Aug 30 18:34 mem
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 mountinfo
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 mounts
-r--------  1 shreyash shreyash 0 Aug 30 18:34 mountstats
dr-xr-xr-x 59 shreyash shreyash 0 Aug 30 18:34 net
dr-x--x--x  2 shreyash shreyash 0 Aug 30 18:34 ns
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 numa_maps
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 oom_adj
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 oom_score
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 oom_score_adj
-r--------  1 shreyash shreyash 0 Aug 30 18:34 pagemap
-r--------  1 shreyash shreyash 0 Aug 30 18:34 patch_state
-r--------  1 shreyash shreyash 0 Aug 30 18:34 personality
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 projid_map
lrwxrwxrwx  1 shreyash shreyash 0 Aug 30 18:34 root -> /
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 sched
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 schedstat
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 sessionid
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 setgroups
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 smaps
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 smaps_rollup
-r--------  1 shreyash shreyash 0 Aug 30 18:34 stack
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 stat
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 statm
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 status
-r--------  1 shreyash shreyash 0 Aug 30 18:34 syscall
dr-xr-xr-x  3 shreyash shreyash 0 Aug 30 18:34 task
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 timens_offsets
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 timers
-rw-rw-rw-  1 shreyash shreyash 0 Aug 30 18:34 timerslack_ns
-rw-r--r--  1 shreyash shreyash 0 Aug 30 18:34 uid_map
-r--r--r--  1 shreyash shreyash 0 Aug 30 18:34 wchan

============================================================================
*/

