/* ************************************************************************
 *       Filename:  func.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年09月03日 14时51分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#ifndef __FUNC_H__
#define __FUNC_H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct app_sta_info{
    char mac[32];
    char ip[32];
    char rssi[32];
    char hostname[32];
    char brand[32];
    char link_time[32];
    char master[32];
}APP_STA_INFO,*APP_STA_INFO_P;

typedef struct app_child_info{
	char mac[32];
	char ip[32];
	char rssi[32];
	char device_name[32];
	char link_time[32];
	char master[32];
	struct app_sta_info sta_info[256];
	unsigned int sta_num; 
}APP_CHILD_INFO,*APP_CHILD_INFO_P;


typedef struct app_main_info{
	int sta_num;
	int child_num;
	int neighbor_num;
	APP_STA_INFO sta_info[256];
}APP_MAIN_INFO,*APP_MAIN_INFO_P;


typedef struct app_mesh_logy{

	char ip[32];
	char mac[32];
	unsigned int rssi;
}APP_MESH_LOGY,* APP_MESH_LOGY_P;


#endif
