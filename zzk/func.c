/* ************************************************************************
 *       Filename:  func.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年09月03日 14时53分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "func.h"




int app_init_sta(APP_STA_INFO_P sta_info)
{

	if(sta_info == NULL)
		return -1;
	strcpy(sta_info->ip, "127.0.0.1");
	strcpy(sta_info->mac, "00:00:00:00:00:00");
	strcpy(sta_info->rssi, "60");
	strcpy(sta_info->link_time, "14:50");
	

	return 0;
}


int app_add_sta_to_main(APP_STA_INFO_P sta_info, APP_MAIN_INFO_P main_info)
{
	int i;
	printf("app_add_sta_to_main\n");
	//i = main_info->sta_num;
	printf("main_info->sta_num = %d\n", main_info->sta_num);
	printf("aa\n");
	printf("sta_info->ip = %s\n", sta_info->ip);
	memcpy(&main_info->sta_info[i], sta_info, sizeof(struct app_main_info));
	printf("bb\n");
	printf("main_info->sta_info[i].ip = %s\n", main_info->sta_info[i].ip);

	main_info->sta_num++;
	return 0;
}


int transform_min_to_time(unsigned int min, char *p_time)
{
	unsigned int sec = 0;
	printf("min = %d\n", min);
	if (min<0)
	{
		strcpy(p_time, "00:00");
		return -1;
	}

	memset(p_time, 0, sizeof(p_time));
	
	sec = min%60;
	min = min/60;

	sprintf(p_time, "%02d:%02d", min, sec);
	
	return 0;
}



