/* ************************************************************************
 *       Filename:  str_to_mac.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年08月02日 09时38分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
#include <string.h>

/* 022311667782 to 02:23:11:66:77:82 */
int str_to_mac(char *p_str, char *buffer)
{
	int i;
	int step = 0;
	memset(buffer, 0, sizeof(buffer));

	
	printf("in mac buffer = %s\n", p_str);
	if (strlen(p_str)!= 12)
		return -1;

	for(i=0; i<5; i++)
	{
		strncat(buffer, p_str+step, 2);
		strcat(buffer, ":");
		step+=2;
	}

	strncat(buffer, p_str+step, 2);
	printf("out of mac buffer = %s\n", buffer);
	return 0;
}

int main(int argc, char *argv[])
{
	char *a="a20122334455";
	char mac[32] = {0};
	str_to_mac(a,mac);
	printf("mac = %s\n", mac);
	return 0;
}


