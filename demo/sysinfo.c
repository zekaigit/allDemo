/* ************************************************************************
 *       Filename:  sysinfo.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年08月19日 11时57分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

/*
struct sysinfo {
      long uptime;          /* 启动到现在经过的时间 */
      unsigned long loads[3];  
      /* 1, 5, and 15 minute load averages */
      unsigned long totalram;  /* 总的可用的内存大小 */
      unsigned long freeram;   /* 还未被使用的内存大小 */
      unsigned long sharedram; /* 共享的存储器的大小*/
      unsigned long bufferram; /* 共享的存储器的大小 */
      unsigned long totalswap; /* 交换区大小 */
      unsigned long freeswap;  /* 还可用的交换区大小 */
      unsigned short procs;    /* 当前进程数目 */
      unsigned long totalhigh; /* 总的高内存大小 */
      unsigned long freehigh;  /* 可用的高内存大小 */
      unsigned int mem_unit;   /* 以字节为单位的内存大小 */
      char _f[20-2*sizeof(long)-sizeof(int)]; 
      /* libc5的补丁
};

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sysinfo.h>


int main(int argc, char *argv[])
{

	struct sysinfo info;
	unsigned long sec, mn, hr, day;


	sysinfo(&info);	

	sec = (unsigned long) info.uptime ;
	day = sec / 86400;
	//day -= 10957; // day counted from 1970-2000

	sec %= 86400;
	hr = sec / 3600;
	sec %= 3600;
	mn = sec / 60;
	sec %= 60;	
	printf("up		time = %ld\n", info.uptime);
	printf("%dday:%dh:%dm:%ds\n",day, hr, mn, sec);

	return 0;
}


